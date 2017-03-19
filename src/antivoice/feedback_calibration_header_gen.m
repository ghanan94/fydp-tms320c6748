% This file is for reading in the dump from the board
% of feedback calibration data, parsing the text,
% determining the roundtrip delay in samples, and
% the magnitude of sound which re-enters the microphone.

%% Parse Feedback Calibration Data Dump into matrices

infilename = 'feedback_calibration_dump.txt';

fid = fopen(infilename);

tline = fgetl(fid);

MODE_SENT = 0;
MODE_RECEIVED = 1;

a = 0; %amplitude index into matrix
f = 0; %frequency index into matrix
MAX_AMP_INDEX = 100;
MAX_FREQ_INDEX = 128;
MAX_CALIB_SAMPLES = 1000;

matrix_sent_str = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX);
matrix_received_str = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX);

matrix_sent_float = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX, MAX_CALIB_SAMPLES);
matrix_received_float = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX, MAX_CALIB_SAMPLES);

%initialize matrices with empty strings
for i = 1 : MAX_AMP_INDEX
    for j = 1 : MAX_FREQ_INDEX
        matrix_sent_str(i,j) = '';
        matrix_received_str(i,j) = '';
    end
end

currentmode = MODE_SENT;
while ischar(tline)
    n = length(tline);
    if length(strfind(tline,'amp_index')) > 0
        istart = strfind(tline,'=') + 1;
        a = unsigned(tline(istart:n)); 
    elseif length(strfind(tline,'freq_index')) > 0
        istart = strfind(tline,'=') + 1;
        f = unsigned(tline(istart:n));
    elseif length(strfind(tline,'sent')) > 0
        currentmode = MODE_SENT;
    elseif length(strfind(tline,'received')) > 0
        currentmode = MODE_RECEIVED;
    elseif length(strfind(tline,'.')) > 0
        %this is actual data that needs to be stored
        if currentmode == MODE_SENT
            matrix_sent_str(a,f) = strcat(matrix_sent_str(a,f), tline);
        else
            matrix_received_str(a,f) = strcat(matrix_received_str(a,f), tline);
        end
    else
        %this would be a blank line
    end
        
    % get next line (fgetl removes newline character)
    tline = fgetl(fid);
end

% Now we wamt tp split the data strings into the 3D matrix as floats

for a = 1 : MAX_AMP_INDEX
    for f = 1 : MAX_FREQ_INDEX
        sent_splits = strsplit(matrix_sent_str(a,f), ',');
        received_splits = strsplit(matrix_received_str(a,f), ',');
        if length(sent_splits) > 0
            for i = 1 : length(sent_splits)
                matrix_sent_float(a,f,i) = float(sent_splits(i));
            end
        end
        
        if length(received_splits) > 0
            for i = 1 : length(received_splits)
                matrix_received_float(a,f,i) = float(received_splits(i));
            end
        end
    end
end

fclose(fid);

%matrix sent float and matrix received float
% contain the calibration data points

%% Possible todo: we could filter the received signal with a BPF for time domain accuracy

%% Calculate roundtrip delay in number of samples

% This requires finding the first peak in the received signal
% since the generated tone is a cosine wave (first sample is a 1.0 * amplitude)
% we want to use amplitudes of 0.8 to 1.0 for this
% this is a = 80 to 100

MIN_RECEIVED_SIGNAL = float(0.2);

abs_sum = zeros(MAX_CALIB_SAMPLES);
calibrated_samples_delay = zeros(MAX_FREQ_INDEX);

for f = 1 : MAX_FREQ_INDEX
    for a = 80 : 100
        for i = 1 : MAX_CALIB_SAMPLES
            abs_sum(i) = abs_sum(i) + abs(matrix_received_float(a,f,i));
        end
    end
    % we want to find the first index i with a significant jump
    for i = 2 : MAX_CALIB_SAMPLES
        if abs_sum(i) > (20 * 0.2 + abs_sum(i - 1))
            % we found that jump
            calibrated_samples_delay(f) = i;
            break;
        end
        %note: if calibrated_samples_delay is zero - that is not practical
    end
end


%% Calculate feedback magnitude
%the value calculated here will be subtracted
%by feedback elimination algorithm in frequency domain
%the amplitude in time domain scales linearly with magnitude
%in frequency domain

calibrated_magnitude = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX);
% we want the percentage of the amount sent that came back
calibrated_magnitude_pct = zeros(MAX_AMP_INDEX, MAX_FREQ_INDEX);

for a = 1 : 100
    for f = 1: MAX_FREQ_INDEX
        calibrated_magnitude(a,f) = max(matrix_received_float(a,f,calibrated_samples_delay(f)), matrix_received_float(a,f,calibrated_samples_delay(f)+1));
        calibrated_magnitude_pct(a,f) = calibrated_magnitude(a,f) / matrix_received_float(a,f,1);
    end
end

% write calibrated magnitude pct to a .h file
outfilename = 'feedback_calibration_data.h';

fileID = fopen(outfilename,'w');
% create the header text
fprintf(fileID, 'This file was automatically generated!\n');
fprintf(fileID, 'Generated by: feedback_calibration_header_gen.m\n\n\n');

%start the 2D lookup table
fprintf(fileID, 'float feedback_calibration_pct[%d][%d] = {\n', MAX_FREQ_INDEX, MAX_AMP_INDEX);

for f = 1 : MAX_FREQ_INDEX
    fprintf(fileID, '{');
    for a = 1 : MAX_AMP_INDEX
        if a < MAX_AMP_INDEX
            fprintf(fileID, '%f,', calibrated_magnitude_pct(a,f));
        else
            fprintf(fileID, '%f', calibrated_magnitude_pct(a,f));
        end
    end
    if f < MAX_FREQ_INDEX
        fprintf(fileID, '},\n');
    else
        fprintf(fileID, '}\n');
    end
end
%end the data structure
fprintf(fileID, '};\n');

fprintf(fileID, ''); %newline at end of file