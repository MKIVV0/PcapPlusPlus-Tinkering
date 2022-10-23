#include <iostream>
//#include </opt/PcapPlusPlus-22.05/Dist/header/IpAddress.h>
#include </usr/include/pcapplusplus/IpAddress.h>
#include </usr/include/pcapplusplus/IPv4Layer.h>
#include </usr/include/pcapplusplus/PcapFileDevice.h>
//#include <PcapFileDevice.h>

int main(int argc, char** argv) {
    // open a pcap file for reading
    pcpp::PcapFileReaderDevice reader("1_packet.pcap");
    /*
    if (!reader.open()) {
        std::cerr << "Error opening the pcap file" << std::endl;
        return 1;
    } */

    // read the first packet from the file
    /*
    pcpp::RawPacket rawPacket;
    if (!reader.getNextPacket(rawPacket)) {
        std::cerr << "Couldn't read the first packet in the file" << std::endl;
        return 1;
    }

    reader.close();
    */

    return 0;
}