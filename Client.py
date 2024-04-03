import socket

HOST = "127.0.0.1"
PORT = 8888

BUFFER_SIZE = 1024


def main():
    data = ""

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((HOST, PORT))

        while data != "Goodbye":
            # Sending the message to the server
            print("Sending 'Hello' to server")
            sock.sendall(b"Hello")

            # Receiving the message from the server
            data = sock.recv(BUFFER_SIZE).decode()
            print(f"SERVER: {data}\n")

            # Terminating the connection with the server
            print("Sending 'exit' to server")
            sock.sendall(b"exit")
            data = sock.recv(BUFFER_SIZE).decode()
            print(f"SERVER: {data}")

        print("Closing connection...")
        sock.close()

    except socket.error as e:
        print(f"Socket error {e}")


if __name__ == "__main__":
    main()
