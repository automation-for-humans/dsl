<div align="center">
    <img
        src="./images/logo.png"
    />
    <h1>dsl-for-humans</h1>
    <p>
        The lex and yacc definitions and the compiler for the [DSL] in [automation-for-humans].
    </p>
</div>

## Usage
To compile :

```bash
make all
```

To parse an input file say, <a href="sample-inputs/public-sites/github-nav-demo.txt"><code>sample-inputs/public-sites/github-nav-demo.txt</code></a>, type :
```bash
# No need to give .txt extension
make validate src=sample-inputs/public-sites/github-nav-demo
```

## English Keywords
<table>
    <tr>
        <th>Keyword</th>
        <th>Use</th>
        <th>Example</th>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>open</code></a></td>
        <td>Used to open a url/application</td>
        <td>
            <a href="#english-keywords"><code>open "https://github.com/"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>click</code></a></td>
        <td>Used to click on an element</td>
        <td>
            <a href="#english-keywords"><code>click on "Issues"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>type</code></a></td>
        <td>Used to type a string in some element</td>
        <td>
            <a href="#english-keywords"><code>type "afh-random-user" in "Pick a username"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>wait</code></a></td>
        <td>Wait's for a particular amount of time in seconds</td>
        <td>
            <a href="#english-keywords"><code>wait for "10"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>hover</code></a></td>
        <td>Used to hover over an element</td>
        <td>
            <a href="#english-keywords"><code>hover on "Fragments"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#english-keywords"><code>execjs</code></a></td>
        <td>Used to execute javascript inside the browser context</td>
        <td>
            <a href="#english-keywords"><code>execjs "localStorage.setItem('random-key', 'false');"</code>
        </td>
    </tr>
</table>
## Advanced Keywords Use

<table>
    <tr>
        <th>Keyword</th>
        <th>Use</th>
        <th>Example</th>
    </tr>
    <tr>
        <td><a href="#advanced-keywords-use"><code>click</code></a></td>
        <td>Used to click on an element with id "issues-id"</td>
        <td>
            <a href="#advanced-keywords-use"><code>click on "issues-id" "id"</code>
        </td>
    </tr>
        <tr>
        <td><a href="#advanced-keywords-use"><code>shortcut</code></a></td>
        <td>Keyboard shortcut</td>
        <td>
            <a href="#advanced-keywords-use"><code>shortcut "command+v" in "Search"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#advanced-keywords-use"><code>click if present</code></a></td>
        <td>Used to click on an element if its present</td>
        <td>
            <a href="#advanced-keywords-use"><code>click if present on "issues-id"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#advanced-keywords-use"><code>type</code></a></td>
        <td>Used to type a string in some element with class name "#user-name"</td>
        <td>
            <a href="#advanced-keywords-use"><code>type "afh-random-user" in "#user-name" "class"</code>
        </td>
    </tr>
</table>

### Resolving ambiguity

<table>
    <tr>
        <th>Keyword</th>
        <th>Use</th>
        <th>Example</th>
    </tr>
    <tr>
        <td><a href="#resolving-ambiguity"><code>click</code></a></td>
        <td>Used to click on the 2nd issue</td>
        <td>
            <a href="#advanced-keywords-use"><code>click on 2nd "issue"</code>
        </td>
    </tr>
    <tr>
        <td><a href="#resolving-ambiguity"><code>type</code></a></td>
        <td>Used to type a string in the 4th text box named "enter text here"</td>
        <td>
            <a href="#resolving-ambiguity"><code>type "afh-random-user" in 4th "enter text here"</code>
        </td>
    </tr>
</table>

### Mac OS X UI Automation
<table>
    <tr>
        <th>Keyword</th>
        <th>Use</th>
        <th>Example</th>
    </tr>
    <tr>
        <td><a href="#mac-os-x-ui-automation"><code>wait until</code></a></td>
        <td>Used to wait until the element is visible</td>
        <td>
            <a href="#mac-os-x-ui-automation"><code>wait until "/AXApplication[@AXTitle='Calculator']"</code>
        </td>
    </tr>
</table>


[automation-for-humans]: https://github.com/intuit/automation-for-humans
[DSL]: https://en.wikipedia.org/wiki/Domain-specific_language
