



# 🚉 TRACK TRACER

**Track Tracer** is a robust server-side application designed to manage passenger details for a transportation system. It leverages socket programming to communicate with clients—typically passengers booking train seats—ensuring a smooth and secure booking process.

## 🛠️ **Functionality**

### 📡 Socket Creation and Configuration
- The server establishes a socket using `socket(AF_INET, SOCK_STREAM, 0)` for network communication.
- Configures the server address (`struct sockaddr_in`) to bind to a specific IP address and port.

### 🚀 Server Initialization
- Binds the socket to the specified IP address and port using `bind()`.
- Listens for incoming connections using `listen()`.

### 🤝 Accepting Client Connection
- Upon receiving a connection request (`accept()`), the server establishes a connection with the client.

### 📨 Sending Initial Welcome Message and OTP
- Sends a welcome message (`server_message`) to the client upon connection.
- Generates a random 4-digit OTP (`otp`) and sends it to the client for authentication.

### 🔑 Passkey Verification
- Prompts the client to enter a passkey.
- Compares the received passkey with the generated OTP.
- If the passkey matches, the server proceeds with collecting passenger details.

### 🧳 Collecting Passenger Details
- Requests and receives the passenger's name, age, gender, date of travel, preferred train choice, and seat preference from the client.

### 🎫 Updating Seat Matrix
- Receives the seat selection from the client and updates the seat matrix accordingly.

### 💾 Saving Passenger Information
- Saves the collected passenger details along with the seat allocation in a file named `ticket.txt`.

### 🍽️ Food Ordering
- Offers the client the option to order food during the journey.

### ⚠️ Error Handling
- Catches errors during socket operations and exits gracefully if any operation fails.

## 🎨 **Colorful Console Output**
- Utilizes ANSI color escape codes (defined as macros) to enhance console output with colors for better readability.

## 🚀 **Usage**

1. **Compile and run the server program** on a machine connected to a network:
   ```bash
   gcc server.c -o server
   ```

2. **Run the compiled executable:**
   ```bash
   ./server
   ```

3. **Connect to the server** using a compatible client-side application.
   - Follow the prompts to enter necessary details and complete the booking process.

## 📝 **Notes**

- Ensure the server is running and reachable from the client-side application.
- This program serves as a demonstration and requires further enhancements for robustness, security, and scalability in a real-world scenario.

---
