--DROP DATABASE IF EXISTS Family;
--CREATE DATABASE Family;

-----------------------------------------------------------
-----------------------------------------------------------
-- Create Tables, in order from primary to secondary
DROP TABLE IF EXISTS Marriage;
DROP TABLE IF EXISTS Person;
CREATE TABLE Person (
  PersonID  INT NOT NULL PRIMARY KEY,
  LastName  VARCHAR(15) NOT NULL,
  FirstName  VARCHAR(15) NOT NULL,
  SrJr  VARCHAR(3) NULL,
  MaidenName VARCHAR(15) NULL,
  Gender CHAR(1) NOT NULL, 
  FatherID INT NULL,
  MotherID INT NULL,
  DateOfBirth  DATE  NULL,
  DateOfDeath  DATE  NULL
  );

CREATE INDEX IxPersonName 
  ON Person (LastName, FirstName);
ALTER TABLE Person ADD CONSTRAINT
	FK_Person_Father FOREIGN KEY	(FatherID) REFERENCES Person (PersonID);
ALTER TABLE Person ADD CONSTRAINT
	FK_Person_Mother FOREIGN KEY	(MotherID) REFERENCES Person (PersonID);

CREATE TABLE Marriage (
  MarriageID  INT NOT NULL PRIMARY KEY,
  HusbandID  INT NOT NULL, --FOREIGN KEY REFERENCES Person,
  WifeID  INT NOT NULL,-- FOREIGN KEY REFERENCES Person,
  DateOfWedding DATE NULL,
  DateOfDivorce DATE NULL
  );

ALTER TABLE Marriage ADD CONSTRAINT 
  FK_Person_Husband FOREIGN KEY (HusbandID) REFERENCES Person (PersonID);
ALTER TABLE Marriage ADD CONSTRAINT 
  FK_Person_Wife FOREIGN KEY (WifeID) REFERENCES Person (PersonID);
----------------------------------------------------------------------------
-- Custom Constraints

CREATE TRIGGER Person_Parents
AFTER INSERT OR UPDATE
ON Person
-- check that if the parent is listed that the gender is correct

IF UPDATE (FatherID)
  BEGIN
    -- Incorrect Father Gender
    IF EXISTS(SELECT * FROM Person JOIN Inserted ON Inserted.FatherID = Person.PersonID WHERE Person.Gender = 'F')  
     BEGIN  
        ROLLBACK
        RAISERROR('Incorrect Gender for Father',14,1)
        RETURN
     END 
  END

  -- Invalid Father Age


  -- Father Deceased


IF UPDATE(MotherID)
  BEGIN
    -- Incorrect Mother Gender
    IF EXISTS(SELECT * FROM Person JOIN Inserted ON Inserted.MotherID = Person.PersonID WHERE Person.Gender = 'M')  
      BEGIN  
        ROLLBACK
        RAISERROR('Incorrect Gender for Mother',14,1)
        RETURN
     END 
  END

  -- Invalid Mother age



  -- Mother Deceased


RETURN

----------------------------------------------------------------------------
-- Sample Data

INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(1, 'Halloway', 'Kelly', 'Russell', 'F', NULL, NULL, '02/07/1904','13/5/1987');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(2, 'Halloway', 'James', '1', 'M', NULL, NULL, '12/4/1899','1/5/2001');
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(3,'Miller', 'Karen', 'Conley', 'F', NULL, NULL, '11/9/1909','1/8/1974');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(4, 'Miller', 'Bryan', NULL, 'M', NULL, NULL, '12/4/1902','16/4/1948');

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(5, 'Halloway', 'James', '2', 'M', 2, 1, '19/5/1922','2/2/1992');
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(6, 'Halloway', 'Audry', 'Ross', 'F', 4, 3, '5/8/1928','12/3/2002');

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(7, 'Halloway', 'Corwin', NULL, 'M', 5, 6, '13/3/1961',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(8, 'Campbell', 'Melanie', 'Halloway', 'F', 5, 6, '19/8/1951','28/6/2009');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(9, 'Halloway', 'Dara', NULL, 'F', 5, 6, '12/12/1958','14/4/2010');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(10, 'Halloway', 'James', 3, 'M', 5, 6, '30/8/1953','30/11/2007');

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(11, 'Kidd', 'Kimberly', NULL, 'F', NULL, NULL, '24/7/1963',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(12, 'Halloway', 'Alysia', 'Simmons', 'F', NULL, NULL, '5/3/1953',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(13, 'Ramsey', 'Walter ', NULL, 'M', NULL, NULL, '30/9/1945',NULL);

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(14, 'Halloway', 'Logan', NULL, 'M', 7, 11,'6/2/1994',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(15, 'Ramsey', 'Shannon', NULL, 'F', 13, 8,'1/4/1970',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(16, 'Ramsey', 'Jennifer', NULL, 'F', 13, 8,'1/6/1972','1/6/1972');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(17, 'Halloway', 'Allie', NULL, 'F', 10, 12,'14/8/1979',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(18, 'Halloway', 'Abbie', NULL, 'F', 10, 12,'14/8/1979',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender,  FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(19, 'Halloway', 'James', 4, 'M',10, 12,'24/5/1975',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(20, 'Halloway', 'Grace', 'Stranes', 'F', NULL, NULL,'1/11/1977',NULL);

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(21, 'Halloway', 'James', 5, 'M', 19, 20,'4/9/2007',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(22, 'Halloway', 'Chris', NULL, 'M', 19, 20, '4/7/2003',NULL);

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(23, 'Halloway', 'Joshua', NULL, 'M', NULL, 9,'25/6/1975',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(24, 'Halloway', 'Laura', NULL, 'F', NULL, 9, '29/5/1977',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(25, 'Halloway', 'Katherine', 'Wood', 'F', NULL, NULL,'23/3/1996',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(26, 'Campbell', 'Richard', NULL, 'M', NULL, NULL,'16/1/1941',NULL);

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(29, 'Campbell', 'Adam', NULL, 'M', 26, 8,'30/1/1981',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(30, 'Campbell', 'Amy', 'Johnson', 'F', NULL, NULL,'27/2/1959',NULL);
INSERT INTO  Person (PersonID, LastName, FirstName, MaidenName, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(32, 'Campbell', 'Elizabeth', 'Straka', 'F', NULL, NULL, '24/6/1939','1/1/1972');

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(27, 'Campbell', 'Alexia', NULL, 'F', 26 , 32, '12/8/1970','1/1/1972');
INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(28, 'Campbell', 'Cameron', NULL, 'M', 26, 32,'13/3/1965',NULL);

INSERT INTO  Person (PersonID, LastName, FirstName, SrJr, Gender, FatherID, MotherID, DateOfBirth, DateOfDeath)
  VALUES(31, 'Campbell', 'William', NULL, 'M', 28, 30, '1/1/1987','30/6/1997');


INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(1, 2, 1, '20/6/1920', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(2, 4, 3 , '14/4/1926', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(3, 5,  6, '1/12/1948', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(4, 10, 12 , '1/1/1975', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(5, 13, 8, '2/5/1968', '1/1/1974');
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(6, 14, 25, '14/4/2018', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(7, 26, 8, '4/9/1977', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(8, 19, 20, '25/8/2000', '1/1/2007');
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(9, 28, 30, '2/6/1984', NULL);
INSERT INTO  Marriage(MarriageID, HusbandID, WifeID, DateOfWedding, DateOfDivorce)
  VALUES(10, 26, 32, '14/4/1963', NULL);

SELECT * FROM Person;

--SELECT * FROM Marriage;

