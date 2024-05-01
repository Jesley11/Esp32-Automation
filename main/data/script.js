// Função para ocultar os botões não relacionados ao cômodo selecionado
function exibirComodo(comodoId) {
    const comodos = ["quarto", "sala", "outros"];
    const titulo = document.getElementById("comodo-titulo");

    comodos.forEach(comodo => {
        const container = document.getElementById(comodo);
        container.style.display = "none";
    });

    const containerSelecionado = document.getElementById(comodoId);
    if (containerSelecionado) {
        containerSelecionado.style.display = "block";
        titulo.innerText = "Controle do " + comodoId.charAt(0).toUpperCase() + comodoId.slice(1);
    }
}

document.addEventListener("DOMContentLoaded", () => {
    exibirComodo("quarto");

    const links = document.querySelectorAll(".sidebar a");
    links.forEach(link => {
        link.addEventListener("click", () => {
            const comodoId = link.getAttribute("href").substring(1);
            exibirComodo(comodoId);
        });
    });

    // Função para buscar o estado dos relés do arquivo JSON e atualizar os botões
    function atualizarEstadosDosReles() {
        fetch('/estado_reles.json') // Caminho para o arquivo JSON 
            .then(response => {
                if (response.status === 200) {
                    return response.json();
                }
            })
            .then(data => {
                // Itera sobre os relés no arquivo JSON e atualiza os botões correspondentes
                for (let i = 1; i <= 8; i++) {
                    const releStatus = data["Rele" + i];
                    const buttonId = "rele" + i + "Button";
                    const button = document.getElementById(buttonId);

                    if (button) {
                        if (releStatus === true) {
                            button.style.backgroundColor = "#fad92a"; // Cor para estado Ligado
                        } else if (releStatus === false) {
                            button.style.backgroundColor = "#0074cc"; // Cor para estado Desligado
                        }
                    }
                }
            })
            .catch(error => {
                console.error('Erro:', error);
            });
    }

    // Chame a função para atualizar os estados dos relés quando a página é carregada
    atualizarEstadosDosReles();
});

function controlarRele(endpoint, buttonId) {
    fetch(endpoint)
        .then(response => {
            if (response.status === 200) {
                return response.text();
            }
        })
        .then(data => {
            const button = document.getElementById(buttonId);
            if (button) {
                if (data === "Rele Ligado") {
                    button.style.backgroundColor = "#fad92a";
                } else if (data === "Rele Desligado") {
                    button.style.backgroundColor = "#0074cc";
                }
            }
        })
        .catch(error => {
            console.error('Erro:', error);
        });
}
