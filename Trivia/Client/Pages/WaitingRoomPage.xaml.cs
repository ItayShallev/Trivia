using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for WaitingRoomPage.xaml
    /// </summary>
    public partial class WaitingRoomPage : Page, INotifyPropertyChanged
    {
        private int _usersCount;

        public int MaxUsers { get; set; }

        public int UsersCount
        {
            get { return _usersCount; }
            set
            {
                if (_usersCount != value)
                {
                    _usersCount = value;
                    OnPropertyChanged();
                }
            }
        }

        public WaitingRoomPage(int maxUsers)
        {
            InitializeComponent();
            DataContext = this; // Set the DataContext to the current instance
            MaxUsers = maxUsers;
            UsersCount = 0;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            NavigationService.GoBack();
        }

        private void BtnStartGame_Click(object sender, RoutedEventArgs e)
        {
            UsersCount++;
        }
    }
}