// DSA Project - Song Playlist 
#include <iostream>
#include <string>
#include <vector>            // amna kashif
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;        // bareera amjad 


struct Song {     //Muqaddisa Rashid
    string title;
    string artist;
    bool favorite;
    Song* next;
    Song* prev;
   

    Song(string t = "", string a = "") {          // constructor  
        title = t;
        artist = a;
        favorite = false;
        next = NULL;
        prev = NULL;
    }
};
                         //Ayesha Abbasi
class RecentlyPlayed {
    Song* head;
    int count;

public:
    RecentlyPlayed() {                    //Last 5 recent songs will be displayed
        head = NULL;
        count = 0;
    }

    void add(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        s->next = head;
        head = s;
        count++;

        if (count > 5) {
            Song* t = head;
            Song* prev = NULL;
            int c = 1;
            while (t && c < 5) {
                prev = t;
                t = t->next;
                c++;
            }
            if (prev) prev->next = NULL;
            delete t;
            count = 5;
        }
    }

    void show() {
        if (!head) {
            cout << "No songs played recently." << endl;
            return;
        }
        cout << "Recently Played:" << endl;
        Song* t = head;
        int i = 1;
        while (t) {
            cout << i << ". " << t->title << " - " << t->artist << endl;
            t = t->next;
            i++;
        }
    }
};

class Playlist {
    string name;
    Song* head;
    Song* tail;
    Song* current;
    int repeatMode; // 0 = Off, 1 = Repeat One, 2 = Repeat All
    RecentlyPlayed recent;

public:
    Playlist(string n = "My Playlist") { //constructor
        name = n;
        head = tail = current = NULL;
        repeatMode = 0;
    }

    string getName() {
        return name;
    }
void addSong(const string& title, const string& artist) {
        Song* s = new Song(title, artist);
        if (!head) head = tail = s;
        else {
            tail->next = s;
            s->prev = tail;
            tail = s;
        }
        cout << "Added: " << title << endl;
    }

    void deleteSong(const string& title) {
        Song* t = head;
        while (t && t->title != title)
            t = t->next;

        if (!t) {
            cout << "Song not found." << endl;
            return;
        }

        if (t == head)
            head = t->next;

        if (t == tail)
            tail = t->prev;

        if (t->prev)
            t->prev->next = t->next;

        if (t->next)
            t->next->prev = t->prev;

        if (t == current)
            current = head;

        delete t;
        cout << "Song deleted." << endl;
    }

    void simulatePlay() {
        cout << "Playing ";
        for (int i = 0; i < 10; i++) {
            cout << "? ";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        cout << endl;
    }

    void playSong() {
        if (!head) { cout << "No songs!\n"; return; }
        if (!current) current = head;

        cout << "\nNow Playing: " << current->title << " - " << current->artist << endl;

        simulatePlay();
        recent.add(current->title, current->artist);

        if (repeatMode == 1) playSong();
        else if (current->next) current = current->next;
        else if (repeatMode == 2) current = head;
    }

    void nextSong() {
        if (!head) return;
        if (!current) current = head;
        if (current->next) current = current->next;
        else { cout << "End of playlist!\n"; return; }
        playSong();
    }
 void prevSong() {
        if (!head) return;
        if (!current) current = head;
        if (current->prev) current = current->prev;
        else { cout << "Start of playlist!\n"; return; }
        playSong();
    }

    void showSongs(bool onlyFav = false) {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << name << ":" << endl;
        Song* t = head;
        int i = 1;
        while (t) {
            if (!onlyFav || t->favorite) {
                cout << i << ". " << t->title << " - " << t->artist;
                if (t->favorite) cout << " (Fav)";
                if (t == current) cout << " (Playing)";
                cout << endl;
            }
            t = t->next;
            i++;
        }
    }

    void shuffleSongs() {
        vector<Song*> arr;
        for (Song* t = head; t; t = t->next) arr.push_back(t);
        if (arr.empty()) {
            cout << "Playlist is empty." << endl;
            return;
        }
        srand((unsigned)time(0));
        for (int i = 0; i < (int)arr.size(); i++) {
            int r = rand() % arr.size();
            swap(arr[i]->title, arr[r]->title);
            swap(arr[i]->artist, arr[r]->artist);
            swap(arr[i]->favorite, arr[r]->favorite);
        }
        cout << "Playlist shuffled." << endl;
    }

    void search(const string& key) {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* t = head;
        bool found = false;

        while (t) {
            if (t->title.find(key) != string::npos || t->artist.find(key) != string::npos) {
                cout << t->title << " - " << t->artist << endl;
                found = true;
            }
            t = t->next;
        }

        if (!found) cout << "No matches found." << endl;
    }

    void edit(const string& oldTitle) {
        Song* t = head;
        while (t && t->title != oldTitle) t = t->next;

        if (!t) {
            cout << "Song not found." << endl;
            return;
        }

        cout << "New title:" << endl;
        getline(cin, t->title);
        cout << "New artist:" << endl;
        getline(cin, t->artist);
        cout << "Updated." << endl;
    }

    void toggleFavorite(const string& title) {
        Song* t = head;
        while (t && t->title != title) t = t->next;
        if (!t) {
            cout << "Song not found." << endl;
            return;
        }
        t->favorite = !t->favorite;
        if (t->favorite) cout << "Added to favorites." << endl;
        else cout << "Removed from favorites." << endl;
    }

    void showRecent() { recent.show(); }

    void setRepeatMode() {
        int choice;
        cout << "Choose repeat mode:" << endl;
        cout << "1. Repeat One" << endl;
        cout << "2. Repeat All" << endl;
        cout << "3. Off" << endl;
        cout << "Enter your choice (1-3): " << endl;
        cin >> choice;
        cin.ignore();

        if (choice == 1) repeatMode = 1;
        else if (choice == 2) repeatMode = 2;
        else repeatMode = 0;
    }

    void simulateSearch() {
        cout << "Searching";
        for (int i = 0; i < 5; i++) {
            cout << "." << flush;
            this_thread::sleep_for(chrono::milliseconds(400));
        }
        cout << endl;
    }
};

class PlaylistManager {
    vector<Playlist> playlists;
    int currentIndex;

public:
    PlaylistManager() {
        playlists.push_back(Playlist("Default"));
        currentIndex = 0;
    }

    Playlist& current() { return playlists[currentIndex]; }

    void deletePlaylist() {
        if (playlists.size() <= 1) {
            cout << "Cannot delete the only playlist." << endl;
            return;
        }

        cout << "Select playlist to delete:" << endl;
        for (int i = 0; i < playlists.size(); i++)
            cout << (i + 1) << ". " << playlists[i].getName() << endl;

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= playlists.size()) {
            playlists.erase(playlists.begin() + (choice - 1));
            currentIndex = 0;
            cout << "Playlist deleted. Switched to: " << playlists[currentIndex].getName() << endl;
        }
        else cout << "Invalid selection." << endl;
    }

    void showAllPlaylists() {
        cout << "All Playlists:" << endl;
        for (int i = 0; i < playlists.size(); i++) {
            cout << (i + 1) << ". " << playlists[i].getName();
            if (i == currentIndex) cout << " (Current)";
            cout << endl;
        }
    }

    void createPlaylist() {
        string name;
        cout << "Enter new playlist name:" << endl;
        getline(cin, name);
        playlists.push_back(Playlist(name));
        currentIndex = playlists.size() - 1;
        cout << "Created and switched to: " << name << endl;
    }

    void switchPlaylist() {
        if (playlists.empty()) {
            cout << "No playlists available." << endl;
            return;
        }

        cout << "Available Playlists:" << endl;
        for (int i = 0; i < playlists.size(); i++)
            cout << (i + 1) << ". " << playlists[i].getName() << endl;

        int choice;
        cout << "Enter playlist number to switch:" << endl;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= playlists.size()) currentIndex = choice - 1;
        else cout << "Invalid selection." << endl;
    }
};

int main() {
    system("color E4");
    PlaylistManager pm;
    int choice = -1;

    while (choice != 0) {
        cout << "\n  ===================================" << endl;
        cout << "      MUSIC PLAYLIST SYSTEM" << endl;
        cout << "     Current Playlist: " << pm.current().getName() << endl;
        cout << "  ====================================" << endl;

        cout << "1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Display Songs" << endl;
        cout << "4. Play Song" << endl;
        cout << "5. Next / Previous" << endl;
        cout << "6. Shuffle Songs" << endl;
        cout << "7. Search / Edit Song" << endl;
        cout << "8. Mark Favorite / Unfavorite" << endl;
        cout << "9. Show Favorites" << endl;
        cout << "10. Show Recently Played" << endl;
        cout << "11. Repeat Mode" << endl;
        cout << "12. Manage Playlists" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter choice:" << endl;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string t, a;
                cout << "Enter title:" << endl; getline(cin, t);
                cout << "Enter artist:" << endl; getline(cin, a);
                pm.current().addSong(t, a);
                break;
            }
            case 2: {
                string t;
                cout << "Enter title to delete:" << endl; getline(cin, t);
                pm.current().deleteSong(t);
                break;
            }
            case 3:
                pm.current().showSongs(false);
                break;
            case 4:
                pm.current().playSong();
                break;
            case 5: {
                cout << "1. Next  2. Previous" << endl; int c; cin >> c; cin.ignore();
                if (c == 1) pm.current().nextSong(); else pm.current().prevSong();
                break;
            }
            case 6:
                pm.current().shuffleSongs();
                break;
            case 7: {
                cout << "1. Search  2. Edit" << endl;
                int c; cin >> c; cin.ignore();
                if (c == 1) {
                    string k;
                    cout << "Enter keyword:" << endl; getline(cin, k);
                    pm.current().simulateSearch();
                    pm.current().search(k);
                }
                else {
                    string k;
                    cout << "Enter title to edit:" << endl; getline(cin, k);
                    pm.current().edit(k);
                }
                break;
            }
            case 8: {
                string t;
                cout << "Enter title:" << endl; getline(cin, t);
                pm.current().toggleFavorite(t);
                break;
            } 
             case 9:
                pm.current().showSongs(true);
                break;
            case 10:
                pm.current().showRecent();
                break;
            case 11:
                pm.current().setRepeatMode();
                break;
            case 12: {
                cout << "1. New Playlist  2. Switch Playlist" << endl;
                int c; cin >> c; cin.ignore();
                if (c == 1) pm.createPlaylist(); else pm.switchPlaylist();
                break;
            }
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}