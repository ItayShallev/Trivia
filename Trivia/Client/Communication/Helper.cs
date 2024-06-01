using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Client.Communication
{
    public class Helper
    {
        /// <summary>
        /// Build a request following the Trivia's protocol
        /// </summary>
        public static string BuildRequest(string requestId, string jsonMessage)
        {
            string messageLength = (jsonMessage.Length).ToString().PadLeft(Constants.NUM_ZEROS_TO_PAD, '0');        // Padding the message length with zeros

            return requestId + messageLength + jsonMessage;
        }

        /// <summary>
        /// Sends the selected request with the given parameters to the server
        /// </summary>
        public static void SendRequest(string requestId, string jsonMessage)
        {
            string message = Helper.BuildRequest(requestId, jsonMessage);
            Communicator.Connection.SendMessage(message);
        }

        /// <summary>
        /// Returns the server's response in the dedicated response structure
        /// </summary>
        public static T GetResponse<T>()
        {
            ResponseInfo responseInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());

            return JsonSerializer.Deserialize<T>(responseInfo.Message);
        }

        /// <summary>
        /// Returns a ResponseInfo structure with the given response-buffer data
        /// </summary>
        public static ResponseInfo GetResponseInfo(string buffer)
        {
            ResponseInfo responseInfo = new ResponseInfo
            {
                ResponseId = buffer.Substring(Constants.RESPONSE_ID_INDEX, Constants.RESPONSE_ID_LENGTH),
                MessageLength = Int32.Parse(buffer.Substring(Constants.MESSAGE_LENGTH_INDEX, Constants.MESSAGE_LENGTH_LENGTH)),
                Message = buffer.Substring(Constants.MESSAGE_INDEX)
            };

            return responseInfo;
        }
    }
}
