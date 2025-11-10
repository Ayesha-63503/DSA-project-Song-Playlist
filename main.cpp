// DSA Project - Song Playlist 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>

using namespace std;
class RecentlyPlayed {
    Song* head;             //Bareera Amjad
    int count;

public:
    RecentlyPlayed() {
        head = nullptr;
        count = 0;
    }

    void addRecent(string title, string artist) {
        Song* song = new Song(title, artist);
        song->next = head;
        head = song;
        count++;

        if (count > 5) {
            Song* temp = head;
            Song* prev = nullptr;
            int c = 1;
            while (temp && c < 5) {
                prev = temp;
                temp = temp->next;
                c++;
            }
            if (temp && prev) {
                prev->next = nullptr;
                delete temp;
                count = 5;
            }
        }
    }

    void showRecent() {
        if (head == nullptr) {
            cout << endl << "No songs have been played recently!" << endl;
            return;
        }

        cout << endl << "Recently Played Songs:" << endl;
        Song* current = head;
        int index = 1;

        while (current != nullptr) {
            cout << index++ << "." << current->title << "—" << current->artist << endl;
            current = current->next;
        }
    }
};
 void simulatePlay() {
    cout << "Playing ";
    for (int i = 0; i < 10; i++) {
        cout << "? ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200)); // small delay to simulate playback
    }
    cout << endl;
}

void playSong() {                                                                               //Ayesha Abbasi
    if (!head) { cout << "No songs!\n"; return; } // check if playlist is empty
    if (!current) current = head; // start from first song if none selected
                 
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
