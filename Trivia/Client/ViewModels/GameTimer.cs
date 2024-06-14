using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace Client.ViewModels
{
    public class GameTimer : INotifyPropertyChanged
    {
        private DispatcherTimer _timer;
        private int _timeElapsed;

        public int TimeElapsed
        {
            get { return _timeElapsed; }
            set
            {
                if (_timeElapsed != value)
                {
                    _timeElapsed = value;
                    OnPropertyChanged();
                }
            }
        }

        public GameTimer()
        {
            
        }

        public void StartTimer()
        {
            // Clearing the old timer if it already exists
            if (_timer != null)
            {
                _timer.Stop();
                _timer.Tick -= Timer_Tick;
                _timer = null;
            }

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += Timer_Tick;
            TimeElapsed = 0;
            _timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeElapsed++;
            
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
