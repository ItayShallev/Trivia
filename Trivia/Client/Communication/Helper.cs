using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Client.Communication
{
    public class Helper
    {
        public static string BuildRequest(int responseId, string jsonMessage)
        {
            string messageLength = (jsonMessage.Length).ToString().PadLeft(Constants.NUM_ZEROS_TO_PAD, '0');        // Padding the message length with zeros

            return responseId + messageLength + jsonMessage;
        }
    }
}
