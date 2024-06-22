using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Client.Communication
{
    public class Socket
    {
        private System.Net.Sockets.Socket _clientSocket;
        private readonly IPAddress _serverAddress;
        private readonly int _serverPort;

        public Socket(string serverIp, int serverPort)
        {
            _serverAddress = IPAddress.Parse(serverIp);
            _serverPort = serverPort;
        }

        public void Start()
        {
            try
            {
                _clientSocket = new System.Net.Sockets.Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                _clientSocket.Connect(new IPEndPoint(_serverAddress, _serverPort));
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());      // We can display a message on the GUI itself...
            }
        }

        public void SendMessage(string message)
        {
            try
            {
                byte[] msg = Encoding.ASCII.GetBytes(message);
                _clientSocket.Send(msg);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
        }

        public string ReceiveMessage()
        {
            byte[] buffer = new byte[2048];
            int bytesReceived = _clientSocket.Receive(buffer);
            return Encoding.ASCII.GetString(buffer, 0, bytesReceived);
        }

        public void CloseConnection()
        {
            _clientSocket.Shutdown(SocketShutdown.Both);
            _clientSocket.Close();
        }
    }
}
