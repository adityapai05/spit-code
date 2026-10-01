CREATE DATABASE sem1_dbms;
USE sem1_dbms;

CREATE TABLE branch_40 (
    bname VARCHAR(18),
    city VARCHAR(18),
    PRIMARY KEY (bname)
);

CREATE TABLE customer_40 (
    cname VARCHAR(18),
    city VARCHAR(18),
    PRIMARY KEY (cname)
);

CREATE TABLE deposit_40 (
    actno VARCHAR(5),
    cname VARCHAR(18),
    bname VARCHAR(18),
    amount DECIMAL(8,2),
    adate DATE,
    PRIMARY KEY (actno),
    FOREIGN KEY (bname) REFERENCES branch_40(bname),
    FOREIGN KEY (cname) REFERENCES customer_40(cname)
);

CREATE TABLE borrow_40 (
    loan_no VARCHAR(5),
    cname VARCHAR(18),
    bname VARCHAR(18),
    amount DECIMAL(8,2),
    PRIMARY KEY (loan_no),
    FOREIGN KEY (bname) REFERENCES branch_40(bname),
    FOREIGN KEY (cname) REFERENCES customer_40(cname)
);

INSERT INTO branch_40 (bname, city) VALUES
('vrce', 'nagpur'),
('ajni', 'nagpur'),
('karolbagh', 'delhi'),
('chandni', 'delhi'),
('dharampeth', 'nagpur'),
('m.g.road', 'bangalore'),
('andheri', 'mumbai'),
('virar', 'mumbai'),
('nehru place', 'delhi'),
('powai', 'mumbai');

INSERT INTO customer_40 (cname, city) VALUES
('anil', 'kolkata'),
('sunil', 'delhi'),
('mehul', 'baroda'),
('mandar', 'patna'),
('madhuri', 'nagpur'),
('pramod', 'nagpur'),
('sandip', 'surat'),
('shivani', 'mumbai'),
('kranti', 'mumbai'),
('naren', 'mumbai');

INSERT INTO deposit_40 (actno, cname, bname, amount, adate) VALUES
('100', 'anil', 'vrce', 1001, '1995-03-01'),
('101', 'sunil', 'ajni', 5000, '1996-01-04'),
('102', 'mehul', 'karolbagh', 3500, '1995-11-17'),
('104', 'madhuri', 'chandni', 1200, '1995-12-17'),
('105', 'pramod', 'm.g.road', 3000, '1996-03-27'),
('106', 'sandip', 'andheri', 2000, '1996-03-31'),
('107', 'shivani', 'virar', 1001, '1995-09-05'),
('108', 'kranti', 'nehru place', 5000, '1995-07-02'),
('109', 'naren', 'powai', 7000, '1995-08-10');

INSERT INTO borrow_40 (loan_no, cname, bname, amount) VALUES
('201', 'anil', 'vrce', 1000),
('206', 'mehul', 'ajni', 5000),
('311', 'sunil', 'chandni', 3000),
('321', 'madhuri', 'andheri', 2000),
('375', 'pramod', 'virar', 8000),
('481', 'kranti', 'nehru place', 3000);
