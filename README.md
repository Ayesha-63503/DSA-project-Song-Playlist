# DSA-project-Song-Playlist
🎵 Song Playlist Simulation (DSA Project)

A Data Structures & Algorithms project that simulates a Music Playlist using a Doubly Linked List.
This project allows users to add songs, delete songs, search songs, mark favorites, and navigate forward/backward just like a real playlist.

🚀 Features
✔ Add Song

Insert a new song with title and artist into the playlist.

✔ Delete Song

Remove any song by title.

✔ Search Song

Find if a song exists in the playlist.

✔ Mark as Favorite

Mark or unmark any song as favorite.

✔ Display All Songs

Show complete playlist with details.

✔ Display Favorite Songs

List only songs marked as favorite.

✔ Next & Previous Song

Move forward or backward using the doubly linked list structure.

🧠 Data Structure Used

We used a Doubly Linked List, where each node contains:

struct Song {
    string title;
    string artist;
    bool favorite;   // true = favorite, false = not favorite
    Song* next;      // pointer to next song
    Song* prev;      // pointer to previous song
};

Why Doubly Linked List?

Easy forward & backward navigation

Efficient insertions and deletions

Perfect for playlist simulations

📂 Project Structure
├── main.cpp        # Contains main menu and logic
├── playlist.cpp    # Doubly Linked List functions
├── playlist.h      # Struct + function declarations
├── README.md       # Documentation

🛠 Functions Implemented
🔹 Insertion

Add a new song at the end of playlist.

🔹 Deletion

Remove a song by title.

🔹 Search

Find a song by title and show its details.

🔹 Mark Favorite / Unfavorite

Toggle favorite = true/false.

🔹 Display Playlist

Print all songs in order.

🔹 Display Favorites

Print only favorite songs.

🔹 Next & Previous

Traverse using next and prev pointers.

💻 How to Run

Clone this repository

git clone https://github.com/your-username/song-playlist-simulation.git


Go to project directory

cd song-playlist-simulation


Compile

g++ main.cpp -o playlist


Run

./playlist

📸 Sample Output
1. Add Song
2. Delete Song
3. Search Song
4. Mark Favorite
5. Display Playlist
6. Display Favorites
7. Next Song
8. Previous Song
9. Exit

📘 Learning Outcomes

This project demonstrates understanding of:

Doubly Linked List (DLL)

Pointers (next, prev)

Structs and constructors

Dynamic memory management

Menu-driven programs

Basic simulation logic in C++

🤝 Contributing

Pull requests are welcome.
If you'd like to add new features (shuffle, sorting, repeating), feel free to fork the project.

📄 License

This project is released under the MIT License. 
