#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Reader {  
public:
    virtual ~Reader() {}
    virtual void parse(string& url) = 0;
};

class ResourceReader {
private:
    Reader* reader;
public:
    ResourceReader(Reader* r) : reader(r) {}
    ~ResourceReader() {delete reader; }

    void setStrategy(Reader* r){
    if (reader != nullptr) delete reader;
    reader = r;
    }

    void read(string& url){
    reader->parse(url);
    }
};

class NewsSiteReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from site" << url << endl;
    } 
};

class SocialNetworkReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from social network" << url << endl;
    } 
};

class TelegramChannelReader : public Reader {
public:
    void parse(string& url) override {
        cout << "Parsing from telegram" << url << endl;
    }
};

int main()
{
    ResourceReader* resourceReader = new ResourceReader(new NewsSiteReader());
    vector<string> linkCollection = vector<string>();

    string url = "https://news.com";
    resourceReader->read(url);
    linkCollection.push_back(url);

    url = "https://facebook.com";
    resourceReader->setStrategy(new SocialNetworkReader());
    linkCollection.push_back(url);

    url = "@news_channel_tg";
    resourceReader->setStrategy(new TelegramChannelReader());
    resourceReader->read(url);
    linkCollection.push_back(url);

    for(auto link : linkCollection ) {
        cout << link << " ";
    }

    
    return 0;
}