using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public static class Constants
    {
        // ************************** SERVER CONSTANTS *************************
        public const string SERVER_IP = "127.0.0.1";
        public const int SERVER_PORT = 8888;

        // ************************** COMMUNICATION PROTOCOL CONSTANTS *************************
        public const int RESPONSE_ID_INDEX = 0;
        public const int RESPONSE_ID_LENGTH = 2;
        public const int MESSAGE_LENGTH_INDEX = 2;
        public const int MESSAGE_LENGTH_LENGTH = 4;
        public const int MESSAGE_INDEX = 6;
        
        public const int NUM_ZEROS_TO_PAD = 4;

        public enum RoomState
        {
            Waiting = 0,
            Playing = 1,
            Finished = 2 // future use?
        };

        // ************************** REQUEST & RESPONSE ID'S *************************
        public const string LogoutRequestId = "00";
        public const string LoginRequestId = "01";
        public const string SignupRequestId = "02";
        public const string MenuRequestId = "03";
        public const string CreateRoomRequestId = "04";
        public const string GetRoomsRequestId = "05";
        public const string GetPlayersInRoomRequestId = "06";
        public const string JoinRoomRequestId = "07";
        public const string GetStatisticsRequestId = "08";
        public const string GetHighScoreRequestId = "09";
        public const string CheckIfUserExistsRequestId = "10";

        public const string LogoutResponseId = "00";
        public const string LoginResponseId = "01";
        public const string SignupResponseId = "02";
        public const string ErrorResponseId = "03";
        public const string GetRoomsResponseId = "04";
        public const string GetPlayersInRoomResponseId = "05";
        public const string GetHighScoreResponseId = "06";
        public const string GetPersonalStatsResponseId = "07";
        public const string JoinRoomResponseId = "08";
        public const string CreateRoomResponseId = "09";
        public const string CheckIfUserExistsResponseId = "10";
        public const string CloseRoomResponseId = "11";
        public const string StartGameResponseId = "12";
        public const string GetRoomStateResponseId = "13";
        public const string LeaveRoomResponseId = "14";
    }
}
