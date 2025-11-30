// DSA Project - Song Playlist 

#include <iostream>
#include <string>
#include <vector>            // amna kashif
#include <fstream>
#include <cstdlib>                     //Ayesha Abbasi
#include <ctime>

// bareera amjad 

using namespace std;
 struct Song {    //structutr  //Muqaddisa Rashid
    string title;
    string artist;
    bool favorite;
    Song* next;
    Song* prev;
   //muqaddisa

  Song(string t = "", string a = "") {          // constructor  

        title = t;
        artist = a;
        favorite = false;
        next = NULL;
        prev = NULL;
    }
};
class RecentlyPlayed {
    Song* head;
    int count;

public:
    RecentlyPlayed() {
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
//increment to shuffling of songs
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
    recent.addRecent(current->title, current->artist);                // add song to recent list

    // Handle repeat and auto-next logic
    if (repeatMode == 1) playSong(); // repeat current
    else if (current->next) current = current->next;         // go to next
    else if (repeatMode == 2) current = head; // loop to start
}

void nextSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->next) current = current->next;
    else { cout << "End of playlist!\n"; return; }                // no next song
    playSong(); // play next
}

void prevSong() {
    if (!head) return;
    if (!current) current = head;
    if (current->prev) current = current->prev;
    else { cout << "Start of playlist!\n"; return; }               // no previous song
    playSong(); // play previous
}
 
    // Searches for songs by title or artist keyword                               //Ayesha Abbasi
void search(const string& key) {                                                                                   
    if (!head) {  
        cout << "Playlist is empty." << endl;                             // No songs available  
        return;  
    }
    
    Song* t = head;  
    bool found = false;  
 
    while (t) {                                                                   // Traverse playlist to find matching songs 
         
        if (t->title.find(key) != string::npos || t->artist.find(key) != string::npos) {              // Match keyword with title OR artist  
            cout << t->title << " - " << t->artist << endl;  // Print match  
            found = true;  
        }
        t = t->next;                                                  // Move to next song  
    }

    if (!found) cout << "No matches found." << endl;  // No result  
}

                                             
void edit(const string& oldTitle) {           // Edits the title and artist of a specific song                  
    Song* t = head;  

    // Find the song with given title  
    while (t && t->title != oldTitle) t = t->next;  

    if (!t) {  
        cout << "Song not found." << endl;  // Target not found  
        return;  
    }

     
    cout << "New title:" << endl;              // Get updated title  
    getline(cin, t->title);

    // Get updated artist  
    cout << "New artist:" << endl;      // Get updated artist
    getline(cin, t->artist);

    cout << "Updated." << endl;       // Confirmation message  
}


// Amna Kashif

class Song {
public:
    string title;
    string artist;
    Song* next;
    Song* prev;

class Playlist {
    string name;
    Song* head;
    Song* tail;
    Song* current;
    int repeatMode; // 0 = Off, 1 = Repeat One, 2 = Repeat All
    RecentlyPlayed recent;
public:
     //constructor
    Playlist(string n = "My Playlist") {
        name = n;
        head = tail = current = NULL;
        repeatMode = 0;
    }


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


                               // Ayesha Abbasi
                              // recently played songs 
    void showRecent() {
        recent.show();
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

// amna kashif
// getName()
    string getName() {
        return name;
    }
    
    // amna kashif
    //  addSong()
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
// amna kashif 
// delete song function
void deleteSong(const string& title) {        // Start deleting a track from playlist
        Song* t = head;                       // Begin from the first track
        while (t && t->title != title)     
            t = t->next;                      //Move to the next track

        if (!t) {                             // ❗ Track not found in playlist
            cout << "Song not found." << endl;
            return;                         
        }

        if (t == head)                      
            head = t->next;                   

        if (t == tail)                        // 🎶 If the track is the last one
            tail = t->prev;                   // 👈 Move playlist tail backward

        if (t->prev)                          // 🔗 Connect previous track to next track
            t->prev->next = t->next;

        if (t->next)                          // 🔗 Connect next track to previous track
            t->next->prev = t->prev;

        if (t == current)                    
            current = head;                   // 🔁 Restart from first track

        delete t;                             
        cout << "Song deleted." << endl;      // ✔️ Deletion complete
}
//muqaddisa 
class PlaylistManager {
    vector<Playlist> playlists; // list of all playlists
    int currentIndex;            // index of the active playlist

public:
    //  Constructor 
    PlaylistManager() {
        playlists.push_back(Playlist("Default")); // default playlist
        currentIndex = 0;
    }

    //Get current playlist
    Playlist& current() {
        return playlists[currentIndex];
    }

    // Create a new playlist
    void createPlaylist() {
        string name;
        cout << "Enter new playlist name:" << endl;
        getline(cin, name);
        playlists.push_back(Playlist(name));
        currentIndex = playlists.size() - 1; // switch to new playlist
        cout << "Created and switched to: " << name << endl;
    }

    //Switch to existing playlist 
    void switchPlaylist() {
        if (playlists.empty()) {
            cout << "No playlists available." << endl;
            return;
        }

        cout << "Available Playlists:" << endl;
        for (int i = 0; i < playlists.size(); i++) {
            cout << (i + 1) << ". " << playlists[i].getName() << endl;
        }

        int choice;
        cout << "Enter playlist number to switch:" << endl;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= playlists.size()) {
            currentIndex = choice - 1;
            cout << "Switched to playlist: " << playlists[currentIndex].getName() << endl;
        } else {
            cout << "Invalid selection." << endl;
        }
    }

    //  Delete a playlist 
    void deletePlaylist() {
        if (playlists.size() <= 1) {
            cout << "Cannot delete the only playlist." << endl;
            return;
        }

        cout << "Select playlist to delete:" << endl;
        for (int i = 0; i < playlists.size(); i++) {
            cout << (i + 1) << ". " << playlists[i].getName() << endl;
        }

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= playlists.size()) {
            playlists.erase(playlists.begin() + (choice - 1));
            currentIndex = 0; // reset to default
            cout << "Playlist deleted. Switched to: " << playlists[currentIndex].getName() << endl;
        } else {
            cout << "Invalid selection." << endl;
        }
    }

    // Show all playlists
    void showAllPlaylists() {
        cout << "All Playlists:" << endl;
        for (int i = 0; i < playlists.size(); i++) {
            cout << (i + 1) << ". " << playlists[i].getName();
            if (i == currentIndex) cout << " (Current)";
            cout << endl;
        }
    }
};
// amna kashif
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
