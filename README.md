# TCPClient
Rules:
1)Generate id
2)Send number L (to generate number of trials)
3)Guess number
4)Try again/win/lose

Example package:
id#01/op#GEN/time#12:00:00.000/odp#123123/
id-user identifier
op-operation
odp-answer

Operations (R-request, A-answer, S-serwer, C-client):
-GEN - generate id 
C=> R:id#/op#GEN/time#12:00:00.000/odp#/
S=> A:id#4/op#GEN/time#12:00:00.100/odp#/

-NUM - send num L (necessary to generate number of trials)
C=> R:id#4/op#NUM/time#12:00:00.000/odp#5/
S=> A:id#4/op#NUM/time#12:00:00.100/odp#5/

-ATT - send trials
S=> R:id#4/op#ATT/time#12:00:00.000/odp#10/
C=> A:id#4/op#ATT/time#12:00:00.100/odp#win/

TRY - send result 
S=> R:id#4/op#TRY/time#12:00:00.000/odp#10/
C=> A:id#4/op#TRY/time#12:00:00.100/odp#win/
