-- 1 and 2

CREATE DATABASE college_40;
USE college_40;



CREATE TABLE student_40 (
    rollno INT,
    name VARCHAR(50)
);

INSERT INTO student_40 VALUES
(1, 'Aditya'),
(2, 'Manav'),
(3, 'Manvith'),
(4, 'Akshat'),
(5, 'Anuj');

-- 3 and 4

CREATE DATABASE Flipkart_40;
USE Flipkart_40;

CREATE TABLE SupplierProducts_40 (
    supplierId INT,
    productId INT,
    PRIMARY KEY (supplierId, productId)
);
