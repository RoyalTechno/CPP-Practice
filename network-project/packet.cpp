#include <iostream>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <unistd.h>
#include <thread>

using namespace std;

enum transport {
	eTCP = 0,
	eUDP = 1,
	eOther = 2,
};

class Packet {
public:
	friend ostream& operator<<(ostream& os, const Packet& p){
		os << p.ipAddr << "\n";
		os << p.macAddr << "\n";
		os << p.getType() << "\n";
		return os;
	}
	Packet(){
		ipAddr = "0.0.0.0";
		macAddr = "::";
		type = eOther;
	}
	Packet(string ip, string mac, transport pktType){
		ipAddr = ip;
		macAddr = mac;
		type = pktType;
	}
	const string& getIP() const { return ipAddr; }
	const string& getMAC() const { return macAddr; }
	const string getType() const{
		switch (type){
			case eTCP:
				return "TCP";
			case eUDP:
				return "UDP";
			break;
		}
		return "Other";
	}
private:
	string ipAddr;
	string macAddr;
	transport type;
};

class captureController{
public:
	captureController(){
		rawSocket = socket(AF_PACKET,SOCK_RAW, htons(ETH_P_ALL));
		buffer = new vector<char>(4096);
		if (rawSocket < 0){
			throw runtime_error("Failed to create socket");
		}
	}
	~captureController(){
		delete buffer;
		delete tCap;
		if (rawSocket >= 0){
			close(rawSocket);
		}
	}
	bool startCapture(){
		if (rawSocket < 0) { return false; }
		tCap = new thread(&captureController::loopCapture, this);
		return true;
	}



private:
        void loopCapture(){
                while(true){
                        int size = recvfrom(rawSocket, buffer->data(), buffer->size(), 0, NULL, NULL);
                        if (size > 0){
                                //Extract Ethernet Header
                                struct ethhdr *eth = (struct ethhdr *)buffer->data();

                                //Extract IP Header (offset by ethernet header size)
                                struct iphdr *iph = (struct iphdr *)(buffer->data() + sizeof(struct ethhdr));

                                struct sockaddr_in source;
                                source.sin_addr.s_addr = iph->saddr;

                                cout << "Captured Packet: Protocol: " << (int)iph->protocol
                                << " | Source IP: " << inet_ntoa(source.sin_addr) << std::endl;

                        }
                }
        }
	vector<char>* buffer;
	int rawSocket;
	thread* tCap;
};

int main(){
	cout << "Starting packet file test:\n";
	Packet  p1("192.80.0.1","FF:23:32:",eTCP);
	cout << p1 << "\n";

	captureController cap;
	cap.startCapture();
	cout << "Started thread" << "\n";
	while (true){
		
	}
}
