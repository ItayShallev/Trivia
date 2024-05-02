import socket
import json

# COMMUNICATION
HOST = "127.0.0.1"
PORT = 8888

BUFFER_SIZE = 1024

# MESSAGES
SIGNUP_MESSAGE_CODE = 1
SIGNUP_MESSAGE = {"username": "user1", "password": "1234", "mail": "user1@gmail.com"}

LOGIN_MESSAGE_CODE = 0
LOGIN_MESSAGE = {"username": "user1", "password": "1234"}

DATA_LENGTH_SIZE = 4

# MENU OPTIONS
EXIT_OPTION = '0'
SIGNUP_OPTION = '1'
LOGIN_OPTION = '2'


def print_menu():
    """
    Prints the menu of options to the screen
    :return: None
    :rtype: None
    """
    print("\n\n0. Exit")
    print("1. Signup")
    print("2. Login")


def send_signup_request(sock):
    """
    Sends a signup request to the server.
    :param sock: The socket to send the request to.
    :return: None
    :rtype: None
    """
    code = str(SIGNUP_MESSAGE_CODE)
    data = json.dumps(SIGNUP_MESSAGE)
    data_length = str(len(data)).zfill(DATA_LENGTH_SIZE)

    signup_request = code + data_length + data

    print(f"CLIENT: {signup_request}")
    sock.sendall(signup_request.encode())


def send_login_request(sock):
    """
    Sends a login request to the server.
    :param sock: The socket to send the request to.
    :return: None
    :rtype: None
    """
    code = str(LOGIN_MESSAGE_CODE)
    data = json.dumps(LOGIN_MESSAGE)
    data_length = str(len(data)).zfill(DATA_LENGTH_SIZE)

    login_request = code + data_length + data

    print(f"CLIENT: {login_request}")
    sock.sendall(login_request.encode())


def main():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((HOST, PORT))

        user_choice = -1

        while user_choice != EXIT_OPTION:
            print_menu()
            user_choice = input("Please select an option: ")

            # Sending the server the chosen message
            if user_choice == SIGNUP_OPTION:
                send_signup_request(sock)
            elif user_choice == LOGIN_OPTION:
                send_login_request(sock)
            elif user_choice == EXIT_OPTION:
                continue
            else:
                print("Invalid option!")
                continue

            # Getting the server's response
            server_response = sock.recv(BUFFER_SIZE).decode()
            print(f"SERVER: {server_response}")

        print("Closing connection...")
        sock.close()

    except socket.error as e:
        print(f"Socket error {e}")


if __name__ == "__main__":
    main()
