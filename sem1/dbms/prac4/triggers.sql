
-- 1. BEFORE INSERT TRIGGER

DELIMITER //

CREATE TRIGGER before_emp_insert
BEFORE INSERT ON emp
FOR EACH ROW
BEGIN
    IF NEW.Working_hours < 0 THEN
        SET NEW.Working_hours = 0;
    END IF;
END //


-- 2. AFTER INSERT TRIGGER
-- insert an audit record whenever a new employee is added

DELIMITER //

CREATE TRIGGER after_emp_insert
AFTER INSERT ON emp_40
FOR EACH ROW
BEGIN
    INSERT INTO emp_audit_40
    VALUES (
        NEW.Name,
        CONCAT(
            'A row has been inserted in emp table at ',
            DATE_FORMAT(NOW(), '%Y-%m-%d at %h:%i:%s %p')
        )
    );
END //

-- 3. BEFORE UPDATE TRIGGER
-- prevent a working date later than today's date

DELIMITER //

CREATE TRIGGER before_emp_update
BEFORE UPDATE ON emp_40
FOR EACH ROW
BEGIN
    IF NEW.Working_Date > CURDATE() THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Working date cannot be greater than today''s date';
    END IF;
END 

//


-- 4. AFTER UPDATE TRIGGER
-- store occupation changes in EmpChanges

DELIMITER //

CREATE TRIGGER after_emp_update
AFTER UPDATE ON emp_40
FOR EACH ROW
BEGIN
    IF (OLD.Occupation <> NEW.Occupation) THEN
        INSERT INTO EmpChanges_40
        VALUES (
            NEW.Name,
            NEW.Occupation,
            OLD.Occupation,
            NOW()
        );
    END IF;
END //


-- 5. BEFORE DELETE TRIGGER
-- archive employee details before deleting the employee

DELIMITER //

CREATE TRIGGER before_emp_delete
BEFORE DELETE ON emp_40
FOR EACH ROW
BEGIN
    INSERT INTO Emp_archieves_40
    VALUES (
        OLD.Name,
        OLD.Occupation,
        OLD.Working_Date,
        OLD.Working_hours,
        NOW()
    );
END 
//


-- 6. AFTER DELETE TRIGGER
-- subtract the deleted employee's working hours from the total

DELIMITER //

CREATE TRIGGER after_emp_delete_40
AFTER DELETE ON emp_40
FOR EACH ROW
BEGIN
    UPDATE Total_working_hours_table_40
    SET Total = Total - OLD.Working_hours;
END //