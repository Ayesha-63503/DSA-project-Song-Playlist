// DSA Project - Song Playl
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <queue>
#include <windows.h> // For UTF-8 console

using namespace std;

// Song Structure 
struct Song {         //muqaddisa Rashid
    string title;
    string artist;
    bool favorite;
    Song* next;
    Song* prev;

    Song(string t = "", string a = "") {
        title = t;
        artist = a;
        favorite = false;
        next = nullptr;
        prev = nullptr;
    }
};

// Recently Played               //bareera Amjad
class RecentlyPlayed {
    Song* head;
    int count;
public:
    RecentlyPlayed() { head = nullptr; count = 0; }

    void add(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        s->next = head;
        head = s;
        count++;
        if (count > 5) {
            Song* t = head;
            Song* prev = nullptr;
            int c = 1;
            while (t && c < 5) { prev = t; t = t->next; c++; }
            if (prev) prev->next = nullptr;
            delete t;
            count = 5;
        }
    }

    void show() {            //amna kashif
        if (!head) { cout << "No songs played recently." << endl; return; }
        cout << "🎵 Recently Played 🎵" << endl;
        Song* t = head;
        int i = 1;
        while (t) {
            cout << i << ". " << t->title << " - " << t->artist << " 🎶" << endl;
            t = t->next;
            i++;
        }
    }
};

//Playlist
class Playlist {                       //amnakashif
    string name;
    Song* head;
    Song* tail;
    Song* current;
    int repeatMode; // 0 = Off, 1 = Repeat One, 2 = Repeat All
    RecentlyPlayed recent;
public:
    Playlist(string n = "My Playlist") { name = n; head = tail = current = nullptr; repeatMode = 0; }
    string getName() { return name; }

    void addSong(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        if (!head) head = tail = s;
        else { tail->next = s; s->prev = tail; tail = s; }
        // Animation
        cout << "Adding \"" << title << "\" to \"" << name << "\" ";
        string anim = "→🎵";
        for (int i = 0; i < 5; i++) { cout << anim; cout.flush(); this_thread::sleep_for(chrono::milliseconds(200)); }
        cout << " ✅" << endl;
    }

    void deleteSong(const string& title) {
        Song* t = head;
        while (t && t->title != title) t = t->next;
        if (!t) { cout << "Song not found." << endl; return; }
        if (t == head) head = t->next;
        if (t == tail) tail = t->prev;
        if (t->prev) t->prev->next = t->next;
        if (t->next) t->next->prev = t->prev;
        if (t == current) current = head;
        delete t;
        cout << "Song deleted. ❌" << endl;
    }

    void simulatePlay() {
        cout << "Playing ";
        string animation = "🎵♪♫🎶";
        for (int i = 0; i < 15; i++) { cout << animation[i % animation.size()] << " "; cout.flush(); this_thread::sleep_for(chrono::milliseconds(200)); }
        cout << endl;
    }

    void playSong() {
        if (!head) { cout << "No songs!\n"; return; }
        if (!current) current = head;
        cout << "\n🎧 Now Playing: " << current->title << " - " << current->artist << " 🎶" << endl;
        simulatePlay();
        recent.add(current->title, current->artist);
        if (repeatMode == 1) playSong();
        else if (current->next) current = current->next;
        else if (repeatMode == 2) current = head;
    }

    void nextSong() { if (!head) return; if (!current) current = head; if (current->next) current = current->next; else { cout << "End of playlist!\n"; return; } playSong(); }
    void prevSong() { if (!head) return; if (!current) current = head; if (current->prev) current = current->prev; else { cout << "Start of playlist!\n"; return; } playSong(); }

    void showSongs(bool onlyFav = false) {
        if (!head) { cout << "Playlist is empty." << endl; return; }
        cout << "🎼 " << name << ":" << endl;
        Song* t = head; int i = 1;
        while (t) {
            if (!onlyFav || t->favorite) {
                if (t->favorite) cout << "❤️ "; else cout << "🎵 ";
                cout << i << ". " << t->title << " - " << t->artist;
                if (t == current) cout << " (Playing)";
                cout << endl;
            }
            t = t->next; i++;
        }
    }

    void shuffleSongs() {         //bareera amjad
        vector<Song*> arr; for (Song* t = head; t; t = t->next) arr.push_back(t);
        if (arr.empty()) { cout << "Playlist is empty." << endl; return; }
        srand((unsigned)time(0));
        for (int i = 0; i < (int)arr.size(); i++) { int r = rand() % arr.size(); swap(arr[i]->title, arr[r]->title); swap(arr[i]->artist, arr[r]->artist); swap(arr[i]->favorite, arr[r]->favorite); }
        cout << "Playlist shuffled ✨" << endl;
    }

    void search(const string& key) {                               // ayesha abbasi
        if (!head) { cout << "Playlist is empty." << endl; return; }
        Song* t = head; bool found = false;
        while (t) {
            if (t->title.find(key) != string::npos || t->artist.find(key) != string::npos) {    //searches the songs based on key
                cout << "🎶 " << t->title << " - " << t->artist << endl;
                found = true;
            }
            t = t->next;
        }
        if (!found) cout << "No matches found." << endl;
    }

    void edit(const string& oldTitle) {                           //editing old title
        Song* t = head; while (t && t->title != oldTitle) t = t->next;
        if (!t) { cout << "Song not found." << endl; return; }
        cout << "New title:" << endl; getline(cin, t->title);
        cout << "New artist:" << endl; getline(cin, t->artist);
        cout << "Updated ✏️" << endl;
    }

    void toggleFavorite(const string& title) {                    //unfavorite and favorite marking
        Song* t = head; while (t && t->title != title) t = t->next;
        if (!t) { cout << "Song not found." << endl; return; }
        t->favorite = !t->favorite;
        if (t->favorite) cout << "Added to favorites ❤️" << endl;
        else cout << "Removed from favorites ❌" << endl;
    }

    void showRecent() { recent.show(); }              //accessing recntly played songs
    void setRepeatMode() {
        int choice; cout << "Choose repeat mode:\n1. Repeat One\n2. Repeat All\n3. Off\nEnter choice: "; cin >> choice; cin.ignore();
        repeatMode = (choice == 1) ? 1 : (choice == 2) ? 2 : 0;             //1=on, 2=All, and 0=off
    }

    void simulateSearch() {             //scearching animation  searching.....
        cout << "Searching"; for (int i = 0; i < 5; i++) { cout << "."; cout.flush(); this_thread::sleep_for(chrono::milliseconds(400)); } cout << endl;
    }
};

// Playlist Manager                  //Muqaddisa Rashid
class PlaylistManager {
    vector<Playlist> playlists;
    int currentIndex;
public:
    PlaylistManager() { playlists.push_back(Playlist("Default")); currentIndex = 0; }
    Playlist& current() { return playlists[currentIndex]; }
    int findPlaylistIndexByName(const string& name) { for (int i = 0; i < (int)playlists.size(); i++) if (playlists[i].getName() == name) return i; return -1; }
    void createPlaylistNamed(const string& name) { playlists.push_back(Playlist(name)); currentIndex = playlists.size()-1; cout << "Created and switched to: " << name << endl; }
    bool addSongToPlaylistByName(const string& playlistName, const string& title, const string& artist) { int idx = findPlaylistIndexByName(playlistName); if(idx<0) return false; playlists[idx].addSong(title, artist); return true; }
    void deletePlaylist() { if(playlists.size()<=1){cout<<"Cannot delete the only playlist."<<endl; return;} cout<<"Select playlist to delete:\n"; for(int i=0;i<playlists.size();i++) cout<<(i+1)<<". "<<playlists[i].getName()<<endl; int choice; cin>>choice; cin.ignore(); if(choice>=1 && choice<=playlists.size()){playlists.erase(playlists.begin()+choice-1); currentIndex=0; cout<<"Deleted. Switched to "<<playlists[currentIndex].getName()<<endl;} else cout<<"Invalid selection."<<endl; }
    void showAllPlaylists() { cout<<"All Playlists:"<<endl; for(int i=0;i<playlists.size();i++){cout<<(i+1)<<". "<<playlists[i].getName(); if(i==currentIndex) cout<<" (Current)"; cout<<endl;}}
    void createPlaylist() { string name; cout<<"Enter new playlist name:\n"; getline(cin,name); playlists.push_back(Playlist(name)); currentIndex=playlists.size()-1; cout<<"Created and switched to: "<<name<<endl; }
    void switchPlaylist() { if(playlists.empty()){cout<<"No playlists available."<<endl; return;} cout<<"Available Playlists:"<<endl; for(int i=0;i<playlists.size();i++) cout<<(i+1)<<". "<<playlists[i].getName()<<endl; int choice; cout<<"Enter playlist number to switch:"; cin>>choice; cin.ignore(); if(choice>=1 && choice<=playlists.size()) currentIndex=choice-1; else cout<<"Invalid selection."<<endl;}
};

//  Available Songs                  //Ayesha Abbasi
void populateAvailableSongs(queue<pair<string,string>>& q) {
    vector<pair<string,string>> songs = {                               //adding default songs to make an avalible list
        {"Blinding Lights","The Weeknd"},{"Shape of You","Ed Sheeran"},{"Someone You Loved","Lewis Capaldi"},
        {"Levitating","Dua Lipa"},{"Dance Monkey","Tones and I"},{"Circles","Post Malone"},{"Perfect","Ed Sheeran"},
        {"Sunflower","Post Malone & Swae Lee"},{"Happier","Marshmello & Bastille"},{"Bad Guy","Billie Eilish"},
        {"Old Town Road","Lil Nas X"},{"Shallow","Lady Gaga & Bradley Cooper"},{"Counting Stars","OneRepublic"},
        {"Believer","Imagine Dragons"},{"Royals","Lorde"},{"Photograph","Ed Sheeran"},{"Watermelon Sugar","Harry Styles"},
        {"Memories","Maroon 5"},{"7 rings","Ariana Grande"},{"Thinking Out Loud","Ed Sheeran"},{"Thunder","Imagine Dragons"},
        {"Rockstar","Post Malone"},{"Lovely","Billie Eilish & Khalid"},{"Senorita","Shawn Mendes & Camila Cabello"},
        {"Can’t Feel My Face","The Weeknd"},{"Girls Like You","Maroon 5"},{"Uptown Funk","Mark Ronson ft. Bruno Mars"},
        {"Let Her Go","Passenger"},{"Viva La Vida","Coldplay"},{"Rolling in the Deep","Adele"},{"Someone Like You","Adele"},
        {"A Sky Full of Stars","Coldplay"},{"Stressed Out","Twenty One Pilots"},{"Lose Yourself","Eminem"},{"Numb","Linkin Park"},
        {"Love Yourself","Justin Bieber"},{"I Will Always Love You","Whitney Houston"},{"Halo","Beyoncé"},{"Grenade","Bruno Mars"},
        {"The Scientist","Coldplay"},{"Yellow","Coldplay"},{"Wake Me Up","Avicii"},{"Clocks","Coldplay"},{"Everybody Hurts","R.E.M."},
        {"Fix You","Coldplay"},{"Demons","Imagine Dragons"},{"Chasing Cars","Snow Patrol"},{"Royals","Lorde"},{"Photograph (Live)","Ed Sheeran"},{"Stay","Rihanna ft. Mikky Ekko"}
    };
    for(auto &p:songs) q.push(p);
}
         //show function
void showAvailableSongs(const queue<pair<string,string>> q) {
    queue<pair<string,string>> temp = q;
    int idx=1;
    cout<<"🎵 Available Songs 🎵"<<endl;
    while(!temp.empty()){auto pr=temp.front(); temp.pop(); cout<<idx<<". "<<pr.first<<" - "<<pr.second<<endl; idx++;}
}
           //using queue to access all of the songs
bool getAvailableSongByIndex(const queue<pair<string,string>>& q,int index,pair<string,string>& out){
    if(index<=0) return false;
    queue<pair<string,string>> temp = q;
    int idx=1;
    while(!temp.empty()){if(idx==index){out=temp.front(); return true;} temp.pop(); idx++; }
    return false;
}

// MAIN 
int main() {
    SetConsoleOutputCP(CP_UTF8); // Enable emojis
    system("color E4");

    PlaylistManager pm;
    int choice=-1;
    queue<pair<string,string>> availableSongs;
    populateAvailableSongs(availableSongs);

    while(choice!=0){
        cout<<"\n==================================="<<endl;
        cout<<"     MUSIC PLAYLIST SYSTEM"<<endl;
        cout<<"    Current Playlist: "<<pm.current().getName()<<endl;
        cout<<"==================================="<<endl;
        cout<<"1. Available Songs\n2. Make Playlists\n3. Add Song\n4. Delete Song\n5. Display Songs\n6. Play Song\n7. Next/Prev\n8. Shuffle\n9. Search/Edit\n10. Favorite\n11. Show Favorites\n12. Recently Played\n13. Repeat Mode\n0. Exit\n";
        cout<<"Enter choice: "; cin>>choice; cin.ignore();

        switch(choice){
            case 1:{
                system("color B0");
                int sub=-1;
                while(sub!=0){
                    cout<<"\n--- AVAILABLE SONGS ---\n";
                    showAvailableSongs(availableSongs);
                    cout<<"Options:\n1. Add to Playlist\n2. Toggle Favorite in Current\n0. Back\nEnter choice: "; cin>>sub; cin.ignore();
                    if(sub==1){
                        int sindex; cout<<"Enter song number: "; cin>>sindex; cin.ignore();
                        pair<string,string> sel;
                        if(!getAvailableSongByIndex(availableSongs,sindex,sel)){cout<<"Invalid song number.\n"; continue;}
                        cout<<"Enter playlist name to add: "; string pname; getline(cin,pname);
                        if(pname.empty()){cout<<"No playlist name. Cancelling.\n"; continue;}
                        int idx = pm.findPlaylistIndexByName(pname);
                        if(idx>=0) pm.addSongToPlaylistByName(pname,sel.first,sel.second);
                        else { cout<<"Playlist not found. Create? (Y/N): "; char yn; cin>>yn; cin.ignore(); if(yn=='Y'||yn=='y'){pm.createPlaylistNamed(pname); pm.addSongToPlaylistByName(pname,sel.first,sel.second);} else cout<<"Song not added.\n"; }
                    } else if(sub==2){
                        int sindex; cout<<"Enter song number to toggle favorite: "; cin>>sindex; cin.ignore();
                        pair<string,string> sel; if(!getAvailableSongByIndex(availableSongs,sindex,sel)){cout<<"Invalid song number.\n"; continue;}
                        pm.current().toggleFavorite(sel.first);
                    } else if(sub==0) break; else cout<<"Invalid choice.\n";
                }
                system("color E4");
                break;
            }
            case 2:{
                cout<<"1. New Playlist 2. Switch 3. Delete 4. Show All\n"; int c; cin>>c; cin.ignore();
                if(c==1) pm.createPlaylist(); else if(c==2) pm.switchPlaylist(); else if(c==3) pm.deletePlaylist(); else if(c==4) pm.showAllPlaylists(); else cout<<"Invalid.\n";
                break;
            }
            case 3:{ string t,a; cout<<"Enter title:"; getline(cin,t); cout<<"Enter artist:"; getline(cin,a); pm.current().addSong(t,a); break; }
            case 4:{ string t; cout<<"Enter title to delete:"; getline(cin,t); pm.current().deleteSong(t); break; }
            case 5: pm.current().showSongs(false); break;
            case 6: pm.current().playSong(); break;
            case 7:{ cout<<"1. Next 2. Previous: "; int c; cin>>c; cin.ignore(); if(c==1) pm.current().nextSong(); else pm.current().prevSong(); break; }
            case 8: pm.current().shuffleSongs(); break;
            case 9:{ cout<<"1. Search 2. Edit: "; int c; cin>>c; cin.ignore(); if(c==1){string k; cout<<"Keyword:"; getline(cin,k); pm.current().simulateSearch(); pm.current().search(k);} else {string k; cout<<"Title to edit:"; getline(cin,k); pm.current().edit(k);} break; }
            case 10:{ string t; cout<<"Enter title to toggle favorite:"; getline(cin,t); pm.current().toggleFavorite(t); break; }
            case 11: pm.current().showSongs(true); break;
            case 12: pm.current().showRecent(); break;
            case 13: pm.current().setRepeatMode(); break;
            case 0: cout<<"Goodbye! 👋"<<endl; break;
            default: cout<<"Invalid choice.\n"; break;
        }
    }
    return 0;
}
