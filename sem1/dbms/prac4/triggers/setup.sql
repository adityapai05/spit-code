
-- main emp table

CREATE TABLE
    emp (
        Name VARCHAR(50),
        Occupation VARCHAR(50),
        Working_Date DATE,
        Working_hours INT
    );

INSERT INTO
    emp
VALUES
    ('Harsh', 'Scientist', '2020-10-21', 12),
    ('Raj', 'Engineer', '2020-08-11', 10),
    ('Ravi', 'Actor', '2020-10-22', 10),
    ('Rahul', 'Doctor', '2020-10-04', 11);

-- table for question 2: after insert audit

CREATE TABLE
    emp_audit_40 (Name VARCHAR(50), audit_description VARCHAR(255));

-- table for question 4: occupation change history

CREATE TABLE
    EmpChanges_40 (
        Name VARCHAR(50),
        New_Occupation VARCHAR(50),
        Old_Occupation VARCHAR(50),
        Updatedat DATETIME
    );

-- table for question 5: deleted employee archive

CREATE TABLE
    Emp_archieves_40 (
        Name VARCHAR(50),
        Occupation VARCHAR(50),
        Working_date DATE,
        WorkingHours INT,
        Deletedat DATETIME
    );

-- table for question 6: total working hours

CREATE TABLE Total_working_hours_table_40 (
    Total INT
);

INSERT INTO Total_working_hours_table_40 (Total)
SELECT SUM(Working_hours)
FROM emp_40;