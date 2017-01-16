/*
   Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This file is licensed under the Apache License, Version 2.0 (the "License").
   You may not use this file except in compliance with the License. A copy of
   the License is located at

    http://aws.amazon.com/apache2.0/

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied. See the License for the
   specific language governing permissions and limitations under the License.
*/
#include <aws/core/Aws.h>

#include <aws/monitoring/CloudWatchClient.h>
#include <aws/monitoring/model/DeleteAlarmsRequest.h>

#include <iostream>

/**
 * Deletes a cloud watch alarm, based on command line input
 */
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: cw_delete_alarm <alarm_name>" << std::endl;
        return 1;
    }

    Aws::String alarmName(argv[1]);

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::CloudWatch::CloudWatchClient cw_client;

    Aws::CloudWatch::Model::DeleteAlarmsRequest deleteAlarmsRequest;
    deleteAlarmsRequest.AddAlarmNames(alarmName);

    auto deleteAlarmsOutcome = cw_client.DeleteAlarms(deleteAlarmsRequest);
    if(!deleteAlarmsOutcome.IsSuccess())
    {
        std::cout << "Failed to delete cloudwatch alarm:" << deleteAlarmsOutcome.GetError().GetMessage() << std::endl;
    }
    else
    {
        std::cout << "Successfully deleted cloudwatch alarm " << alarmName << std::endl;
    }

    Aws::ShutdownAPI(options);

    return 0;
}



