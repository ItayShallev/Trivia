using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.ViewModels
{
    internal class GameResultsEntry
    {
        public string Username { get; set; }
        public uint NumCorrectAnswers { get; set; }
        public uint NumWrongAnswers { get; set; }
        public double AverageAnswerTime { get; set; }
        public uint Points { get; set; }
        public uint Rank { get; set; }

        public bool IsHighlighted { get; set; }


        public GameResultsEntry(string username, uint numCorrectAnswers, uint numWrongAnswers, double averageAnswerTime, uint points, uint rank, bool isHighlighted)
        {
            Username = username;
            NumCorrectAnswers = numCorrectAnswers;
            NumWrongAnswers = numWrongAnswers;
            AverageAnswerTime = averageAnswerTime;
            Points = points;
            Rank = rank;
            IsHighlighted = isHighlighted;
        }
    }
}
