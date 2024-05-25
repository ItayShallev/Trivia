﻿using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
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
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        public CreateRoomPage()
        {
            InitializeComponent();
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            NavigationService.GoBack();
        }

        // Checks if the rooms settings are valid and ready for "CreateRoom" Request
        private bool AreRoomSettingsValid()
        {
            return (MaxPlayersComboBox.Text != "Select number of players") && (RoomNameTextBox.Text != "");
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            if (AreRoomSettingsValid())
            {
                //string message = JsonSerializer.Serialize(new CreateRoomRequest(RoomNameTextBox.Text, MaxPlayersComboBox.Text, ));
                //Communicator.Connection.SendMessage();

                WaitingRoomPage waitingRoomPage = new WaitingRoomPage(int.Parse(MaxPlayersComboBox.Text), (int)QuestionTimerSlider.Value);
                NavigationService.Navigate(waitingRoomPage);
            }
        }
    }
}
