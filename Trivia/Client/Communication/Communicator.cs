using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Communication
{
    public static class Communicator
    {
        public static Socket _conn;

        public static Socket Connection
        {
            get { return _conn; }
        }

        public static async void InitializeConnection()
        {
            _conn = new Communication.Socket(Constants.SERVER_IP, Constants.SERVER_PORT);
            _conn.Start();
        }

        public static void CloseConnection(EventArgs e)
        {
            _conn.CloseConnection();
        }
    }
}
