using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Markup;
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

        public static Constants.RoomStatus StringStatusToRoomStatus(string status)
        {
            if (status == "Waiting") return Constants.RoomStatus.Waiting;
            if (status == "Playing") return Constants.RoomStatus.Playing;
            return Constants.RoomStatus.Closed;
        }

        public static string RoomStatusToStringStatus(Constants.RoomStatus roomStatus)
        {
            if (roomStatus == Constants.RoomStatus.Waiting) return "Waiting";
            if (roomStatus == Constants.RoomStatus.Playing) return "Playing";
            return "Closed";
        }

        public static bool IsValidEmailAddress(string s)
        {
            Regex regex = new Regex(@"^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$");
            return regex.IsMatch(s);
        }

        public static string DecodeAsciiCodes(List<int> asciiCodes)
        {
            // Converting the list of ASCII codes to character array and then to string
            char[] chars = new char[asciiCodes.Count];

            for (int i = 0; i < asciiCodes.Count; i++)
            {
                chars[i] = (char)asciiCodes[i];
            }

            return new string(chars);
        }
    }
}
