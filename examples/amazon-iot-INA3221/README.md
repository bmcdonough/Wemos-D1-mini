# NOTE - 20160525
 * need to change IOTclient from UpdateShadow to Publish

# How-to send INA3221 values to Amazon IOT
1. Initial idea came from here:  https://www.hackster.io/heskew/aws-iot-remote-soil-moisture-monitor-860040
2. Hardware:
  * http://www.wemos.cc/
  * http://store.switchdoc.com/ina3221-breakout-board-3-channel-current-voltage-monitor-grove-headers-compare-to-ina219-grove-headers/
3. Software:
  * https://aws.amazon.com/iot/
4. Libraries:
  * https://github.com/heskew/aws-sdk-arduino

## initial investigation

## code example

## results
 * need to add details for results from URL:
  * https://mobile.awsblog.com/post/TxQRWEM9DK0VNR/Analyze-device-generated-data-with-AWS-IoT-and-Amazon-Elasticsearch-Service


1. Create IAM user:  Identity and Access Management

2. Go to the Amazon Elasticsearch console and create a new domain with name "digital-voltage".

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "AWS": "arn:aws:iam::xxxxxxxxxxxx:user/ElasticUser"
      },
      "Action": "es:*",
      "Resource": "arn:aws:es:us-east-1:xxxxxxxxxxxx:domain/digital-voltage/*"
    }
  ]
}
```
