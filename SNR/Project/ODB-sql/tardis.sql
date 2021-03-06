/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `tardis`;

CREATE TABLE `tardis` (
  `tardis_id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `track_id` INT UNSIGNED NOT NULL,
  `tardis_longitude` DOUBLE NOT NULL,
  `tardis_latitude` DOUBLE NOT NULL,
  `tardis_date` DATETIME NULL)
 ENGINE=InnoDB;

/*
ALTER TABLE `tardis`
  ADD CONSTRAINT `tardis_track_id_fk`
    FOREIGN KEY (`track_id`)
    REFERENCES `track` (`track_id`)
*/

