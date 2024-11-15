# ✔️ Meta State Machine
A high performance headeronly compile time evaluated statemachine.
Big shoutout to [boost::msm](https://www.boost.org/doc/libs/1_86_0/libs/msm/doc/HTML/index.html) for inspiring me to create this project.
I started this project to learn more about template metaprogramming while also making something very usefull for some of my other projects.
It is probably (definitely :sweat_smile:) not as performant as boost::msm since they have put years of reasearch into it and use even less runtime stuff than I do here :)

# Learn more about MSM
Check out the [wiki](https://github.com/K1ngmar/MSM/wiki) to learn more about the msms and its implementation!

# Important to know
By itself the statemachine is not thread safe, if you want to dispatch events from multiple events you would need to handle this yourself in the calls to `ProcessEvent();`.