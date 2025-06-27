# 💣 Bomberman Multiplayer (SFML Networking)

A local network multiplayer Bomberman clone built with SFML. Supports up to 4 players connected over a local IP network.

---

## 🎮 Features

- 🔥 **Up to 4 Players** on one local network  
- 🏠 **Lobby System**  
  - Players can join the lobby and wait for others  
  - Lobby displays if it's full before starting  
  - Real-time **chat** support in lobby  
- 🌐 **Networking:**  
  - **TCP** for reliable messages (power-ups, explosions, block destruction)  
  - **UDP** for fast, real-time player movement updates  
- 🎯 Classic Bomberman mechanics: place bombs, destroy blocks, collect power-ups  
- 🧠 Simple state machine + basic collision system  

---
[![Demo Video](https://img.youtube.com/vi/-uFRr81QabU/0.jpg)](https://youtu.be/-uFRr81QabU)


## 🛠️ Tech Stack

- **Language:** C++  
- **Library:** SFML (Simple and Fast Multimedia Library)  
- **Networking:** SFML TCP and UDP sockets  

---

## 📦 Running Locally

1. Clone the repository:

   ```bash
   git clone https://github.com/MonikaBuk/sfml_networking.git

 ## 📦 Running Locally

1. Build the project using your preferred C++ compiler with **SFML linked**.
2. The project uses the same IP adress for now for security and testin reasons it is on one pc.

---

## 🔧 How It Works

### 🏠 Lobby
- A host runs the server, and clients connect using its IP.
- Lobby allows real-time chat and shows player count.

### 🌐 Networking
- **UDP** is used for real-time movement to reduce latency.
- **TCP** is used for reliable events (e.g., destroying blocks, spawning power-ups, bomb logic).

---

## 🚀 Future Improvements

- 🌍 Support for online matchmaking beyond local network  
- 🎨 Improved UI and animations  
- 👁️ Spectator mode  
- 🧩 Dynamic map generation  
- 📊 In-game score tracking  

---

## 🙋‍♀️ Author

**Monika Buk** – [@MonikaBuk](https://github.com/MonikaBuk)

---

## 📄 License

This project is licensed under the **MIT License**.


