using Client.Communication;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.ViewModels
{
    internal class LeaderboardEntry
    {
        public string Username { get; set; }
        public uint NumGamesPlayed { get; set; }
        public uint NumCorrectAnswers { get; set; }
        public uint NumWrongAnswers { get; set; }
        public double AverageAnswerTime { get; set; }
        public uint Points { get; set; }
        public uint Rank { get; set; }

        public bool IsHighlighted { get; set; }


        public LeaderboardEntry(string username, uint numGamesPlayed, uint numCorrectAnswers, uint numWrongAnswers, double averageAnswerTime, uint points, uint rank)
        {
            Username = username;
            NumGamesPlayed = numGamesPlayed;
            NumCorrectAnswers = numCorrectAnswers;
            NumWrongAnswers = numWrongAnswers;
            AverageAnswerTime = averageAnswerTime;
            Points = points;
            Rank = rank;
            IsHighlighted = false;
        }
    }
}
