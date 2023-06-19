//
// Created by dragosc1 on 19.06.2023.
//

#ifndef OOP_TMPLDECLARATIONS_H
#define OOP_TMPLDECLARATIONS_H

template class Game<double>;
template class Game<float>;
template std::ostream &operator<<(std::ostream &, const Game<double> &);
template std::ostream &operator<<(std::ostream &, const Game<float> &);

#endif //OOP_TMPLDECLARATIONS_H


