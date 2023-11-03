#include <music.h>

// Return value: need choose?
unsigned int listMidiPort(RtMidiOut *rtmidi) {
    unsigned int nPorts = rtmidi->getPortCount();
    if (nPorts == 0)
        std::cout << "No output ports available!" << std::endl;
    for (int i = 0; i < nPorts; i++) {
        std::string portName = rtmidi->getPortName (i);
        std::cout << "  Output port #" << i << ": " << portName << std::endl;
    }
    return nPorts;
}

bool openMidiPort (RtMidiOut *rtmidi) {
    auto nPorts = listMidiPort(rtmidi);
    if (nPorts > 1) {
        unsigned int i = 0;
        do {
            std::cout << "\nChoose a port number: ";
            std::cin >> i;
        } while (i >= nPorts);
        rtmidi->openPort (i);
    } else if (nPorts == 1) 
        rtmidi->openPort (0);
    else
        return false;
    return true;
}

RtMidi::Api chooseMidiApi() {
    std::vector<RtMidi::Api> apis;
    RtMidi::getCompiledApi (apis);

    if (apis.size() <= 1)
        return RtMidi::Api::UNSPECIFIED;

    std::cout << "\nAPIs\n  API #0: unspecified / default\n";
    for (size_t n = 0; n < apis.size(); n++)
        std::cout << "  API #" << apis[n] << ": "
                  << RtMidi::getApiDisplayName (apis[n]) << "\n";

    std::cout << "\nChoose an API number: ";
    unsigned int i;
    std::cin >> i;

    std::string dummy;
    std::getline (std::cin, dummy); // used to clear out stdin

    return static_cast<RtMidi::Api> (i);
}
