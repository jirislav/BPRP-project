% function receiveUDP receives UDP communication from specified address and
% port
function receiveUDP(raspiIP, UDPport, timeout)
% raspiIP - ip adress string
% UDPport - port to receive on
% timeout - time to wait for incoming signal

% open echo server 
echoudp('off')
echoudp('on',UDPport);
% type echoudp('off') to turn echoudp off

% test udp socket
% u = udp('127.0.0.1',4012);

% create socket
u = udp(raspiIP,UDPport);
% set timeout interval
u.Timeout=timeout;
% register callback function
%u.BytesAvailableFcnMode='eosCharCode';
u.DatagramReceivedFcn=@writeDataToStruct;

% open the socket
fopen(u);
% write to socket
fwrite(u,65:74)
%read from socket
fread(u,10);
% close echo server
echoudp('off')
%close the socket
fclose(u);


    function writeDataToStruct(obj,evt)
        % process received datagram
       disp('hello')
       
    end


end


