```Arduino
  publish("busvoltage1", busvoltage1);
  
  void publish(const char *topic, float data) {
    AmazonIOTClient iotClient;
    ActionError actionError;
	
  iotClient.setAWSRegion(awsIotRegion);
  iotClient.setAWSEndpoint(awsIotEndpoint);
  iotClient.setAWSDomain(awsIotDomain);
  iotClient.setAWSPath("/things/digital-voltage/shadow");
  iotClient.setAWSKeyID(awsKeyID);
  iotClient.setAWSSecretKey(awsSecKey);
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);

  Serial.println("Updating thing shadow...");
  
  MinimalString shadow = ("{\"state\":{\"reported\":{\"" + String(topic) + "\":" + String(data, 2) + "}}}").c_str();
  char* result = iotClient.update_shadow(shadow, actionError);
```  
  
  
#  AWSFoundationTypes.h
```Arduino
 /* A wrapper for c_strings that has a deep-copying equality operator and
 * constructor, as well as json serialization and deserialization
 * capabilities. */
class MinimalString {
    /* The wrapped c_string. */
    char* cStr;
    /* True if this string represents an object that is already serialized and
     * therefore does not need to be enclosed in quotes when jsonSerialize()
     * is called. */
    bool alreadySerialized;
    /* Copy the other MinimalString's c_string. */
    void innerCopy(const MinimalString &toCopy);
    /* Delete the c_string if it exists. */
    void innerDelete();
public:
    /* Copy the passed c_string. */
    MinimalString(const char* cStr);
    /* Copy the passed c_string. */
    MinimalString(const char* cStr, int len);
    /* Empty constructor, c_string is NULL. */
    MinimalString();
    /* Coppying constructor. */
    MinimalString(const MinimalString &toCopy);
    /* c_string getter. */
    const char* getCStr() const;
    /* Overload = for deep copying. */
    MinimalString& operator=(const MinimalString &toCopy);
    void setAlreadySerialized(bool alreadySerialized);
    bool getAlreadySerialized() const;
    /* Returns a quoted copy of the string. */
    MinimalString jsonSerialize() const;
    /* Unquotes the string if it has surrounding quotes. */
    bool jsonDeserialize(MinimalString json);
    /* Calculate the length of the string. */
    int length() const;
    ~MinimalString();
};
```

#  AmazonIOTClient.h
```Arduino
// class Shadow {
//     MinimalString shadow;
//     void reset();
// public:
//     void setShadow(shadow) const;
// };



class AmazonIOTClient : public AWSClient4 {
public:
    AmazonIOTClient();

    char* update_shadow(MinimalString shadow, ActionError& actionError);
};

#endif /* AMAZONIOTCLIENT_H_ */
```
