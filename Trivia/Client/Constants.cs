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

        public const int TIME_EXPIRED_ANSWER_ID = 4;

        public enum RoomStatus
        {
            Waiting = 0,
            Playing = 1,
            Closed = 2 // future use?
        };

        public enum QuestionDifficulty
        {
            Easy = 0,
            Medium = 1,
            Hard = 2
        }

        // ************************** REQUEST & RESPONSE ID'S *************************
        public const string LogoutRequestId = "00";
        public const string LoginRequestId = "01";
        public const string SignupRequestId = "02";
        public const string CreateRoomRequestId = "03";
        public const string GetRoomsRequestId = "04";
        public const string GetPlayersInRoomRequestId = "05";
        public const string JoinRoomRequestId = "06";
        public const string GetPersonalStatisticsRequestId = "07";
        public const string GetHighScoreRequestId = "08";
        public const string CheckIfUserExistsRequestId = "09";
        public const string CloseRoomRequestId = "10";
        public const string LeaveRoomRequestId = "11";
        public const string StartGameRequestId = "12";
        public const string GetRoomStateRequestId = "13";
        public const string SubmitAnswerRequestId = "14";
        public const string LeaveGameRequestId = "15";
        public const string GetQuestionRequestId = "16";
        public const string GetGameResultRequestId = "17";


        public const string LogoutResponseId = "00";
        public const string LoginResponseId = "01";
        public const string SignupResponseId = "02";
        public const string CreateRoomResponseId = "03";
        public const string GetRoomsResponseId = "04";
        public const string GetPlayersInRoomResponseId = "05";
        public const string JoinRoomResponseId = "06";
        public const string GetPersonalStatisticsResponseId = "07";
        public const string GetHighScoreResponseId = "08";
        public const string CheckIfUserExistsResponseId = "09";
        public const string CloseRoomResponseId = "10";
        public const string LeaveRoomResponseId = "11";
        public const string StartGameResponseId = "12";
        public const string GetRoomStateResponseId = "13";
        public const string SubmitAnswerResponseId = "14";
        public const string LeaveGameResponseId = "15";
        public const string GetQuestionResponseId = "16";
        public const string GetGameResultResponseId = "17";
        public const string ErrorResponseId = "18";
    }
}
