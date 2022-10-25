#include <iostream>
#include "stdlib.h"
#include <PcapFileDevice.h>

int main(int argc, char* argv[]) {
    /**
     * Use IFileReaderDevice interface to automatically identify the file type (pcap/pcap-ng)
     * and create an interface istance that both readers implement.
     * This method is static.
    */
    pcpp::IFileReaderDevice* reader = pcpp::IFileReaderDevice::getReader("input.pcap");

    if (reader == NULL) {
        std::cerr << "Cannot determine reader for the file type" << std::endl;
        return 1;
    }

    // Open the reader for reading 
    if (!reader->open()) {
        std::cerr << "Cannot open input.pcap for reading" << std::endl;
        return 1;
    }

    /**
    * Creates a pcap file writer. Specify the file name and the link type 
    * the packets that will be written on the file
    */
    pcpp::PcapFileWriterDevice pcapWriter("output.pcap", pcpp::LINKTYPE_ETHERNET);

    // Try opening the file for writing
    if (!pcapWriter.open()) {
        std::cerr << "Cannot open output.pcap for writing" << std::endl;
        return 1;
    }

    /**
     * Creates a pcap-ng file writer. The filename has to be specified and the link
     * type is not necessary, since pcap-ng files can store multiple link types in
     * the same file.
    */
    pcpp::PcapNgFileWriterDevice pcapNgWriter("output.pcapng");
    if (!pcapNgWriter.open()) {
        std::cerr << "Cannot open output.pcapng for writing" << std::endl;
        return 1;
    }

    // set a BPF filter for the reader: only matching packets will be read
    if (!reader->setFilter("net 98.138.19.88")) {
        std::cerr << "Cannot set filter for the file reader" << std::endl;
        return 1;
    }

    // The packet container
    pcpp::RawPacket rawPacket;

    /**
     * This lopp will continue as long as there are matching packets 
     * for the BPF filter
    */
    while (reader->getNextPacket(rawPacket)) {
        pcapWriter.writePacket(rawPacket);
        pcapNgWriter.writePacket(rawPacket);
    }

    // READER/WRITER STATS
    // Stats object
    pcpp::IPcapDevice::PcapStats stats;

    // reads the stats from the reader and prints them
    reader->getStatistics(stats);
    std::cout << "Read " << stats.packetsRecv << " packets successfully and "
        << stats.packetsDrop << " packets could not be read" << std::endl;

    // reads the stats from the pcap writer and prints them
    pcapWriter.getStatistics(stats);
    std::cout << "Written " << stats.packetsRecv << " packets successfully to the pcap writer and " 
    << stats.packetsDrop << " packets could not be written" << std::endl;

    // reads the stats from the pcap writer and prints them
    pcapNgWriter.getStatistics(stats);
    std::cout << "Written " << stats.packetsRecv << " packets successfully to the pcap-ng writer and " 
    << stats.packetsDrop << " packets could not be written" << std::endl;

    reader->close();
    pcapWriter.close();
    pcapNgWriter.close();

    delete reader;

    return 0;
}