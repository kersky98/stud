use Family
go

SELECT * FROM Marriage
SELECT * FROM Person ORDER BY PersonID;


--1) Получить список всех брачных пар и возраст жениха и невесты. Список должен включать: 
--Дату бракосочетания, Имя и фамилию жениха, Возраст жениха, Имя и фамилию невесты, Возраст невесты.
--SELECT m.DateOfWedding, 
--p1.FirstName, p1.LastName, (DATEDIFF(YEAR,p1.DateOfBirth,'22/5/2016')) as Age,
--p2.FirstName, p2.LastName, (DATEDIFF(YEAR,p2.DateOfBirth,'22/5/2016')) as Age
--FROM Person p1
--JOIN Marriage m ON p1.PersonID = m.HusbandId
--JOIN Person p2 ON  p2.PersonID = m.WifeID
--ORDER BY m.DateOfWedding


--2) Сколько лет было матери на момент рождения ее ребенка? 
--Список должен включать: Имя и фамилию матери, Возраст матери, Имя ребенка.
--SELECT p1.FirstName, p1.LastName, (DATEDIFF(YEAR,p1.DateOfBirth,p2.DateOfBirth)) as Age,
--p2.FirstName
--FROM Person p1
--JOIN Person p2 ON p2.MotherID = p1.PersonID
 
 --3) Кто из прародителей (мужчин) имеет наибольшую родословную? 
 --Список должен включать: Имя и фамилию мужчины.
WITH tree (id, fid, fname, lname, level1)
AS (SELECT PersonID, FatherID, FirstName, LastName, 0
FROM Person
WHERE FatherID IS NOT NULL
UNION ALL
SELECT PersonID, FatherID, FirstName, LastName, t.level1 + 1
FROM Person p
INNER JOIN tree t
ON t.fid = p.PersonID)
SELECT id, fname, lname, level1
--SELECT TOP 1 fname, lname
FROM tree
ORDER BY level1 DESC
--WHERE level1=(SELECT MAX(level1) FROM tree)