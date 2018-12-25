# dsl
This is the [DSL] for [automation-for-humans].

## Usage
To compile :
```bash
make all
```

To parse an input file say, `sample-inputs/public-sites/github-nav-demo.txt`, type :
```bash
make validate src=sample-inputs/public-sites/github-nav-demo.txt dest=sample-inputs/public-sites/github-nav-demo.json
```

[automation-for-humans]: https://github.com/intuit/automation-for-humans
[DSL]: https://en.wikipedia.org/wiki/Domain-specific_language
