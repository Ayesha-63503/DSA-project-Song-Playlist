// DSA Project - Song Playlist 

#include <iostream>
#include <string>
#include <vector>            // amna kashif
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>

using namespace std;
class RecentlyPlayed {
    Song* head;
    int count;

public:
    RecentlyPlayed() {
        head = NULL;
        count = 0;
    }

    // ===== RecentlyPlayed Module: add() =====
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

    // ===== RecentlyPlayed Module: show() =====
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

//Bareera Amjad
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

 void simulatePlay() {
    cout << "Playing ";
    for (int i = 0; i < 10; i++) {
        cout << "? ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200)); // small delay to simulate playback
    }
    cout << endl;
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


void playSong() {                                                                               //Ayesha Abbasi
    if (!head) { cout << "No songs!\n"; return; } // check if playlist is empty
    if (!current) current = head; // start from first song if none select
                 
    // Display current song info
    cout << "\n?? Now Playing: " << current->title << " - " << current->artist;
    if (current->favorite) cout << " ?️";
    cout << endl;

    simulatePlay(); // simulate playback animation
    recent.addRecent(current->title, current->artist); // add song to recent list

    // Handle repeat and auto-next logic
    if (repeatMode == 1) playSong(); // repeat current
    else if (current->next) current = current->next; // go to next
    else if (repeatMode == 2) current = head; // loop to start
}

void nextSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->next) current = current->next;
    else { cout << "End of playlist!\n"; return; } // no next song
    playSong(); // play next
}

void prevSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->prev) current = current->prev;
    else { cout << "Start of playlist!\n"; return; } // no previous song
    playSong(); // play previous
}
// Amna Kashif
//module 3,4,5 [playlist data, add/delete, display]
class Song {
public:
    string title;
    string artist;
    Song* next;
    Song* prev;

    Song(const string& t, const string& a) {
        title = t;
        artist = a;
        next = nullptr;
        prev = nullptr;
    }
};

void shuffleSongs() {
    vector<Song*> list;
    Song* temp = head;

    while (temp != NULL) {
        list.push_back(temp);
        temp = temp->next;
    }

    srand(time(0));
    for (int i = 0; i < list.size(); i++) {
        int r = rand() % list.size();
        swap(list[i]->title, list[r]->title);
        swap(list[i]->artist, list[r]->artist);
        swap(list[i]->favorite, list[r]->favorite);
    }

    cout << "Playlist shuffled!" << endl;
}
//increment
void setRepeatMode() {   //bareera amjad
    int choice;
    cout << "Choose repeat mode:" << endl;
    cout << "1. Repeat One" << endl;
    cout << "2. Repeat All" << endl;
    cout << "3. Off" << endl;
    cout << "Enter your choice (1-3): " << endl;
    cin >> choice;

    if (choice == 1) {
        repeatMode = 1;
        cout << "Repeat mode set to: One" << endl;
    } 
    else if (choice == 2) {
        repeatMode = 2;
        cout << "Repeat mode set to: All" << endl;
    } 
    else {
        repeatMode = 0;
        cout << "Repeat mode turned Off" << endl;
    }
}

