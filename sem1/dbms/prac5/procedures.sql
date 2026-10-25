USE classicmodels;

-- Drop the existing procedure before recreating it
DROP PROCEDURE IF EXISTS Get_Orders_Status;


-- Procedure to display the number of orders per year
-- for a given order status

DELIMITER //

CREATE PROCEDURE Get_Orders_Status(
    IN statusVal VARCHAR(15)
)
BEGIN
    SELECT
        YEAR(orderDate) AS `Year`,
        COUNT(orderNumber) AS `Total Orders`
    FROM orders
    WHERE status = statusVal
    GROUP BY YEAR(orderDate)
    ORDER BY YEAR(orderDate);
END //

DELIMITER ;


-- Execution 1: Shipped orders
CALL Get_Orders_Status('Shipped');


-- Execution 2: Cancelled orders
CALL Get_Orders_Status('Cancelled');


-- Execution 3: Orders on hold
CALL Get_Orders_Status('On Hold');