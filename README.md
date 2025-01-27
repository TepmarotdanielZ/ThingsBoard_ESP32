## 1. THINGSBOARD

ThingsBoard is an open-source Internet of Things (IoT) platform designed to facilitate device management, data collection, visualization, and analysis.

![20](images/20.jpg)

**1.1. Key Feature:**

* **Device Management:** Easily register and manage a wide variety of IoT devices.
* **Data Collection:** Supports multiple communication protocols (**`MQTT, HTTP, CoAP`**) for data ingestion.
* **Dashboards & Visualization:** Create customizable dashboards to visualize data in real-time using various widgets.
*	**Rule Engine:** Automate actions based on data conditions or triggers.
*	**User Management:** Role-based access to control user permissions.
*	**Deployment Options:**
    * **Self-Hosted:** The open-source version allows users to run their own instances.
    * **Cloud-Based:** The professional edition provides additional features and support in a hosted environment.
*	**Use Cases:** Ideal for applications in smart cities, industrial automation, environmental monitoring, and agriculture.

## 2. MQTT PROTOCOL WITH ESP32 THINGSBOARD:

**2.1.	Overview:**

MQTT (Message Queuing Telemetry Transport) is a lightweight messaging protocol suitable for IoT applications. ThingsBoard supports MQTT for real-time data transfer from devices such as the ESP32.

**2.2. Prerequisites:**

* **Hardware:**
  * ESP32 Development Board.
  * A DHT sensor (like DHT11 or DHT22) for temperature and humidity data (optional).
 
* **Software:**
  * [Arduino IDE](https://www.arduino.cc/en/software).
  * o	Libraries:
    * **`PubSubClient`** for MQTT.
    * **`DHT sensor library`** (if you are using a DHT sensor).


## 3. CREATE DEVICE ON THINGSBOARD:

For simplicity, we will provide the device manually using the UI.

   * Login to your ThingsBoard instance and navigate to the “**Entities**”. Then click the “**Devices**” page.

   ![1](images/1.jpg)

   * Click on the “`+`” icon in the top right corner of the table and then select “**Add new device**”.

   ![2](images/2.jpg)

   * Input device name. For example, “`SpaceBOT`”. No other changes required at this time. Click “**Add**” to add the device.

   ![3](images/3.jpg)
