using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json;
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
using Client.Communication;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for WaitingRoomPage.xaml
    /// </summary>
    public partial class WaitingRoomPage : Page, INotifyPropertyChanged
    {
        private int _usersCount;

        public int MaxUsers { get; set; }
        public int TimePerQuestion { get; set; }

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

        public WaitingRoomPage(int maxUsers, int timePerQuestion)
        {
            InitializeComponent();
            DataContext = this; // Set the DataContext to the current instance
            UsersCount = 0;
            MaxUsers = maxUsers;
            TimePerQuestion = timePerQuestion;

            //Timer timer = new Timer()
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
            if (UsersCount < MaxUsers)
            {
                ListBoxItem newUserItem = new ListBoxItem();
                newUserItem.Content = "USER " + (UsersCount + 1);

                LBUsersList.Items.Add(newUserItem);

                UsersCount++;
            }
        }

        private void SendGetPlayersInRoomRequest()
        {
            // build and send the request
            string messageContent = JsonSerializer.Serialize(new GetPlayersInRoomRequest());
            string message = Helper.BuildRequest(Client.Constants.LoginRequestId, messageContent);
            Communicator.Connection.SendMessage(message);


            ///////// TODO: DEBUG TO CHECK DESERIALIZER
            // receive the response
            ResponseInfo respInfo = Helper.GetResponseInfo(Communicator.Connection.ReceiveMessage());
        }
    }
}