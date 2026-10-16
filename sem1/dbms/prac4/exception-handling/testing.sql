-- 1) CONTINUE HANDLER
CALL testing_continue_40 ();

-- 2) EXIT HANDLER
CALL testing_exit_40 ();

-- 3) CONTINUE HANDLER FOR DUPLICATES

CALL insert_product_continue_40 (101, 201);

-- 4) EXIT HANDLER FOR DUPLICATES
CALL insert_product_exit_40 (102, 202);