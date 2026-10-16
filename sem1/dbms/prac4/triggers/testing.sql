
-- 1. BEFORE INSERT TRIGGER

INSERT INTO emp_40
VALUES ('Amit', 'Tester', '2020-11-01', -5);
SELECT * FROM emp_40 WHERE Name = 'Amit';


-- 2. AFTER INSERT TRIGGER
-- insert an audit record whenever a new employee is added

INSERT INTO emp_40 
VALUES('Manav', 'Backend Developer', '2026-11-05', '5');

SELECT * FROM emp_audit_40;

-- 3. BEFORE UPDATE TRIGGER
-- prevent a working date later than today's date

UPDATE emp_40
SET Working_Date = '2099-01-01'
WHERE Name = 'Harsh';


-- 4. AFTER UPDATE TRIGGER
-- store occupation changes in EmpChanges

UPDATE emp_40
SET Occupation = 'Professor'
WHERE Name = 'Harsh';

SELECT * FROM EmpChanges_40;


-- 5. BEFORE DELETE TRIGGER
-- archive employee details before deleting the employee

DELETE FROM emp_40
WHERE Name = 'Raj';

SELECT * FROM Emp_archieves_40;


-- 6. AFTER DELETE TRIGGER
-- subtract the deleted employee's working hours from the total

DELETE FROM emp_40
WHERE Name = 'Ravi';

SELECT * FROM emp_40;