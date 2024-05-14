import React, { useState } from 'react';
import { StyleSheet, View, Image, TouchableOpacity } from 'react-native';

import unclicked from './unclicked.png'; // Adjust path as needed
import clicked from './clicked.png'; // Adjust path as needed
import unclickedGreen from './unclickedGreen.png'; // Adjust path as needed
import clickedGreen from './clickedGreen.png'; // Adjust path as needed

// // Configure the AWS IoT device
// const device = AWSIoTData.device({
//   region: 'us-east-1', // Your AWS region (N. Virginia)
//   clientId: 'ButtonApp' + (Math.floor((Math.random() * 100000) + 1)),
//   host: 'iot-fips.us-east-1.amazonaws.com',
//   protocol: 'wss',
//   maximumReconnectTimeMs: 8000,
//   debug: true,
//   accessKeyId: 'AKIAXYKJWECJJRSQVG6S',  // Provide your Access Key ID
//   secretKey: 'ympwpWoUZyBpzclHoYB6a6cfC9gisQ35DSCjvd/P',    // Provide your Secret Access Key
//   sessionToken: '', // Optional session token
// });


export default function App() {
  const [currentImage, setCurrentImage] = useState(unclicked);

  function turnOnLED() {
    fetch('http://192.168.4.1/H')
      .then(response => response.text())  // Assuming the server responds with some text
      .then(data => console.log("LED turned on:", data))
      .catch(error => console.error('Error turning on LED:', error));
  }

  function turnOffLED() {
    fetch('http://192.168.4.1/L')
      .then(response => response.text())  // Assuming the server responds with some text
      .then(data => console.log("LED turned off:", data))
      .catch(error => console.error('Error turning off LED:', error));
  }

  const toggleImage = () => {
    if(currentImage == unclicked) {
      setCurrentImage(clicked); // First, change to the clicked image

      const dataToSend = { color: 'Red button clicked.'};

      turnOffLED();

      setTimeout(() => {
        setCurrentImage(unclickedGreen); // After 100ms, change back to the unclicked image
      }, 100);
    }
    else if (currentImage == unclickedGreen) {
      setCurrentImage(clickedGreen); // First, change to the clicked image

      const dataToSend = { color: 'Green button clicked.'};

      turnOnLED();

      setTimeout(() => {
        setCurrentImage(unclicked); // After 100ms, change back to the unclicked image
      }, 100);  
    }

  };

  return (
    <View style={styles.container}>
      <TouchableOpacity onPress={toggleImage}>
        <Image source={currentImage} style={styles.logo} />
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#FFFFFF',
    alignItems: 'center',
    justifyContent: 'center',
  },
  logo: {
    width: 300, // Set according to your preference
    height: 300, // Set according to your preference
    resizeMode: 'contain', // This ensures the image scales correctly within the size limits
  },
});
