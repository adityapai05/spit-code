-- List names of depositors having same branch as the branch of SUNIL
select cname from deposit_40 where bname=(select bname from deposit_40 where cname='sunil') and cname!='sunil';

-- List LoanNo and LoanAmount of borrowers having the samebranch as the of depositor SUNIL.
select loan_no, amount from borrow_40 where bname=(select bname from deposit_40 where cname='sunil') and cname!='sunil';

-- List all depositors living in NAGPUR.
select cname from deposit_40 where cname in (select cname from customer_40 where city = 'nagpur');

-- List all depositors having deposit in all the branches whereSUNIL is having account.
select cname from deposit_40 where bname in (select bname from deposit_40 where cname='sunil') or bname in (select bname from borrow_40 where cname='sunil');

-- List names of customers having maximum deposit
select cname from deposit_40 where amount in (select max(amount) from deposit_40);

-- List names of customers having maximum deposit in thecustomers living in Nagpur
select cname from deposit_40 where amount = (select max(amount) from deposit_40 where cname in (select cname from customer_40 where city='nagpur'));

-- List the names of branches having highest number ofdepositors.
select bname from deposit_40 group by bname having count(cname) >= all (select count(cname) from deposit_40 group by bname);

-- List the highest deposit of the city where branch of Sunil islocated
select max(amount) from deposit_40 where bname in (select bname from branch_40 where city=(select city from branch_40 where bname in (select bname from deposit_40 where cname='sunil')));

-- List the names of customers having more deposit than theaverage deposit in their respective branches
select cname from deposit_40 group by bname having amount > (select avg(amount) from deposit_40 group by bname);

-- List the names of branches where number of depositors lessthan 2
select bname from deposit_40 group by bname having count(cname) < 2;

-- Count the number of customers living in the city where branchis located.
select count(cname) from customer_40  where city in (select city from branch_40);

-- 12. Change the living city of the VRCE branch borrowers toNagpur.
update customer_40 set city='nagpur' where cname in (select cname from borrow_40 where bname='vrce');

-- 13. Update deposit of Anil. Give him maximum deposit fromdepositors living in city Nagpur.
update deposit_40 set amount=(select max(amount) from deposit_40 where bname in (select bname from branch_40 where city='nagpur')) where cname='anil';

-- 14. Transfer Rs. 100 from account Anil to account Sunil if both arehaving the same branch.
update deposit_40 set amount=amount-100 where cname='anil' and bname=(select bname from deposit_40 where cname='sunil');
update deposit_40 set amount=amount+100 where cname='sunil' and bname=(select bname from deposit_40 where cname='anil');

-- 15. Add Rs. 100 to the account of all those depositors who arehaving the highest deposit amount in their respective branches.
update deposit_40 set amount=amount+100 where amount in (select max(amount) from deposit_40 group by bname);

-- 16. Delete branches having deposit from Nagpur.

-- 17. Delete deposit of Anil and Sunil if both are living in the same city.

-- 18. Delete borrower of branches having minimum number ofcustomers. 

-- 19. List names of customers who are depositors as well asborrowers. 

-- 20. List all the customers who are depositors but not borrowers. 

-- 21. List the depositors having the same living city as Sunil and thesame branch city as Anil. 

-- 22. List the depositors having amount less than 5000 and living inthe city as Shivani. 

-- 23. List the customers who are borrowers or depositors and havingliving city Mumbai andthebranch city same as that of Sandip. 

-- 24. List the branch name and branch wise deposit. 

-- 25. Add 100 to the amount of all depositors having deposit higherthan the average deposit of their branch.

-- 26. List names of depositors who has third highest amount. 

-- 27. List details of depositors according to ascending order ofcustomer names.