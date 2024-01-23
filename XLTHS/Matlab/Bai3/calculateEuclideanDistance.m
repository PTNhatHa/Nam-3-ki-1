
function distance = calculateEuclideanDistance(vector1, vector2)
    % Tính khoảng cách Euclidean giữa hai vector
    distance = sqrt(sum((vector1 - vector2).^2));
    
end
