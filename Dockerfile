FROM ocaml/opam:ubuntu-ocaml-5.2

USER root
RUN apt-get update
RUN apt-get install -y npm
RUN npm install -g http-server yarn

WORKDIR /app
ENV PATH _opam/bin:$PATH
COPY . .

RUN make init
RUN make build

CMD http-server dist
