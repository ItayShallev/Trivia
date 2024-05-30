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
        public static string BuildRequest(string requestId, string jsonMessage)
        {
            string messageLength = (jsonMessage.Length).ToString().PadLeft(Constants.NUM_ZEROS_TO_PAD, '0');        // Padding the message length with zeros

            return requestId + messageLength + jsonMessage;
        }

        public static ResponseInfo GetResponseInfo(string buffer)
        {
            ResponseInfo responseInfo = new ResponseInfo();
            responseInfo.ResponseId = buffer.Substring(Constants.RESPONSE_ID_INDEX, Constants.RESPONSE_ID_LENGTH);
            responseInfo.MessageLength = Int32.Parse(buffer.Substring(Constants.MESSAGE_LENGTH_INDEX, Constants.MESSAGE_LENGTH_LENGTH));
            responseInfo.Message = buffer.Substring(Constants.MESSAGE_INDEX);

            return responseInfo;
        }
    }
}
