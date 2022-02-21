clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a = randi([1 10],1,10)

fprintf('min(a)= %f\n', min(a))
fprintf('max(a)= %f\n', max(a))

fprintf('mean(a)= %f\n', mean(a))

fprintf('median(a)= %f\n', median(a))

fprintf('prctile(a,25)= %f\n', prctile(a,25))

fprintf('mode(a)= %f\n', mode(a)) % Compute the most frequently occurring value in a dataset
