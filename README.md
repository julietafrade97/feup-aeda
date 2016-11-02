# Boleias Partilhadas - ShareIt (nome provisório)
==================
1.º Trabalho de Grupo de AEDA, FEUP

AEDA1617_2MIEIC1_E

Requisitos Obrigatórios:
------------------------
- [ ] Visualização dos Users
- [ ] Visualização do histórico de viagens
- [ ] Ficheiro: Users
- [ ] Ficheiro: Relationships ("buddies")
- [ ] Ficheiro: Trip Record (histórico de viagens realizadas)
- [ ] Associar buddies
...


File Syntax
===========

Source cpp:
----------
= welcomeMenu =
> display do esqueleto do menu
> retorna opcao de inicio de sessão

= main =
> extrai informação dos ficheiros de texto
> chama menu inicial (welcomeMenu)

Agency h/cpp:
----------
> criação de singleton
> variáveis globais, acessiveis a todas as classes: sessionID e sessionPos (ID e posição do "User" no vetor Users - Informação do Login) // vetores Users, Trips, Transactions.

= registerUser =
> menu de registo de um novo user
> adiciona ao vetor Users um novo objeto

= loginUser =
> menu de login de um user
> acede à conta, novo menu e afins

= mainMenu_Admin =
> menu apenas visualizado pelo administrador da agency: credenciais-> admin, admin

= mainMenu_User =
> menu principal de um user

= extractUsers =
> extrai do ficheiro de texto "Users.txt" a informação de todos os users para um vetor Users

= writeUsers =
> guarda toda a informação do vetor Users, no ficheiro de texto

= validUser =
> booleano que retorna de um user "nome" existe

= validPassword =
> booleano que retorna se a password de respetivo user está correta

= findID =
> recebe o nome de um user e retorna respetivo ID

= getPos =
> recebe o ID de um user, e retorna a posição do user no vetor Users (é bastante útil)

= getUsers =
> retorna o vetor Users

= addUser =
> adiciona um novo objeto User ao vetor Users

User h/cpp:
----------
> tem classes derivadas: Driver, Passenger

= getID =
> retorna ID do user

= getName =
> retorna o nome do user

= getPassword =
> retorna password do user

= depoist =
> carrega o saldo (balance) do user com value

= payment =
> faz pagamento à empresa de cada user - VIRTUAL

= car =
> retorna se tem carro ou nao (driver ou passenger) - VIRTUAL

Guest h/cpp:
---------------
= getName =
> retorna nome

= getStart =
> retorna origem da viagem pretendida

= getEnd =
> retorna o destino da viagem pretendida

Trip h/cpp:
---------------
= getDriver =
> retorna o driver

= getStops =
> retorna vetor de paragens da viagem (itinerário)

= getOrigin =
> retorna origem

= getDestination =
> retorna destino
