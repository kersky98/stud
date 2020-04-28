/*
 * header.h
 *
 *  Created on: 25 апр. 2020 г.
 *      Author: user
 */

#ifndef DEMOGRAPHIC_HEADER_H_
#define DEMOGRAPHIC_HEADER_H_

enum class Gender {
  FEMALE,
  MALE
};


struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};


#endif /* DEMOGRAPHIC_HEADER_H_ */
